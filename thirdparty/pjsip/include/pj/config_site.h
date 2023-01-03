#   define PJSIP_MAX_TSX_COUNT		((32*1024)-1)
#   define PJSIP_MAX_DIALOG_COUNT	((32*1024)-1)
//#   define PJSIP_UDP_SO_SNDBUF_SIZE	(1024*1024)
//#   define PJSIP_UDP_SO_RCVBUF_SIZE	(1024*1024)
//#define pj_assert(expr)
#define PJ_LOG_MAX_LEVEL 5
#define PJ_LOG_THREAD_WIDTH 20

// No check udp ip/port changed
#define PJMEDIA_TRANSPORT_SWITCH_REMOTE_ADDR 0

// No convert send udp to tcp
#define PJSIP_DONT_SWITCH_TO_TCP 1

// pjnath
#define PJ_STUN_MAX_PKT_LEN 1600
#define PJNATH_STUN_SOFTWARE_NAME "turn-srv"

// debug
#define PJ_DEBUG 0
#define PJ_TIMER_DEBUG 0

// thread
#undef PJ_HAS_THREADS
#define PJ_HAS_THREADS	1

// ioqueue
//#define PJ_IOQUEUE_MAX_HANDLES 64
#define PJ_IOQUEUE_MAX_EVENTS_IN_SINGLE_POLL 64
#define PJ_IOQUEUE_HAS_SAFE_UNREG 1
#define PJ_IOQUEUE_HAS_WAKEUP 1
#define PJ_IOQUEUE_EPOLL_ENABLE_EXCLUSIVE_ONESHOT  PJ_HAS_THREADS


// turn-srv tx/rx buf size
//#define PJ_TURN_UDP_SOCK_BUF_SIZE	(20*1024*1024)
//#define PJ_TURN_TCP_SOCK_BUF_SIZE	(20*1024*1024)
#define PJ_TURN_SRV_MAX_WORK_THREADS   128
#define PJ_TURN_SOCK_READ_FLAGS     0 //PJ_IOQUEUE_ALWAYS_ASYNC