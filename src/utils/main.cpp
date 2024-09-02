


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
		ms / 1000,    // second
		ms % 1000000  // ns
	};
	nanosleep(&tp, NULL);
#endif
}

