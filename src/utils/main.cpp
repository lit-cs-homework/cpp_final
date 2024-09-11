


#ifdef _WIN32
# include <windows.h>
#else
# include <time.h>
#endif

void ms_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec tp = {
		.tv_sec =   ms / 1000,    // second
		.tv_nsec = (ms % 1000) * 1000000  // ns
	};
	nanosleep(&tp, NULL);
#endif
}

