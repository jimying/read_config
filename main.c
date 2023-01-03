#include <stdio.h>
#include <pjlib.h>
#include <pjlib-util.h>

#define THIS_FILE "main.c"

/**
 * key and value splited by whitespace
 * eg.
 * key1 val1
 * key2 val2
 */
#ifndef SPLIT_SPACE
#define SPLIT_SPACE 0
#endif

/**
 * key and value splited by '='
 * eg.
 * key1=val1
 * key2 = val2
 */

#define SPLIT_EQUAL !SPLIT_SPACE

static void on_syn_err(struct pj_scanner *scanner)
{
    PJ_UNUSED_ARG(scanner);
    PJ_THROW(PJ_EINVAL);
}

int main(int argc, char **argv)
{
    pj_status_t status = 0;
    pj_oshandle_t fd;
    pj_off_t fsize;
    char buf[80 * 1024];
    pj_ssize_t len = sizeof(buf);
    pj_scanner scanner;
    const char *conf_file;

    if (argc != 2)
    {
        printf("Usage: %s config\n", argv[0]);
        return -1;
    }
    conf_file = argv[1];

    pj_init();

    /* read file content */
    status = pj_file_open(NULL, conf_file, PJ_O_RDONLY, &fd);
    if (status != PJ_SUCCESS)
    {
        PJ_PERROR(1, (THIS_FILE, status, "error open file[%s]", conf_file));
        return -1;
    }
    fsize = pj_file_size(conf_file);
    len = fsize;
    pj_file_read(fd, buf, &len);
    pj_file_close(fd);

    /* start parse */
    PJ_USE_EXCEPTION;
    pj_scan_init(&scanner, buf, len, 0, on_syn_err);

    PJ_TRY
    {
        while (!pj_scan_is_eof(&scanner))
        {
            pj_str_t k, v;
            /* Ignore whitespace */
            if (pj_isspace(*scanner.curptr))
            {
                scanner.curptr++;
                continue;
            }

            /* Ignore comment line */
            if (*scanner.curptr == '#')
            {
                pj_scan_skip_line(&scanner);
                continue;
            }

            /* Get key, value */
#if SPLIT_SPACE
            /**
             * key and value splited by whitespace
             * eg.
             * key1 val1
             * key2 val2
             */
            pj_scan_get_until_chr(&scanner, " \t\r\n", &k);
            if (*scanner.curptr == ' ' || *scanner.curptr == '\t')
                pj_scan_advance_n(&scanner, 1, PJ_TRUE);
            pj_scan_get_until_chr(&scanner, "\r\n", &v);
#else
            /**
             * key and value splited by '='
             * eg.
             * key1=val1
             * key2 = val2
             */
            pj_scan_get_until_chr(&scanner, "=\r\n", &k);
            if (*scanner.curptr == '=')
                pj_scan_advance_n(&scanner, 1, PJ_TRUE);
            pj_scan_get_until_chr(&scanner, " \t\r\n", &v);
#endif
            pj_strtrim(&k);
            pj_strtrim(&v);

            printf("[%.*s] -> [%.*s]\n", (int)k.slen, k.ptr, (int)v.slen,
                   v.ptr);
        }
    }
    PJ_CATCH_ANY
    {
        status = PJ_GET_EXCEPTION();
    }
    PJ_END
    pj_scan_fini(&scanner);

    pj_shutdown();
    return status;
}
