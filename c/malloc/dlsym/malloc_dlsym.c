
static bool performance_enabled_ = false;
static void* (*sys_malloc)(size_t) = 0;
static void* (*sys_realloc)(void*,size_t) = 0;
static void* (*sys_calloc)(size_t,size_t) = 0;
static void (*sys_free)(void*) = 0;
 
static void initialize_functions()
{	
	sys_malloc = reinterpret_cast<void*(*)(size_t)>(dlsym(RTLD_NEXT, "malloc"));
	sys_realloc = reinterpret_cast<void*(*)(void*,size_t)>(dlsym(RTLD_NEXT, "realloc"));
	sys_calloc = reinterpret_cast<void*(*)(size_t,size_t)>(dlsym(RTLD_NEXT, "calloc"));
	sys_free = reinterpret_cast<void(*)(void*)>(dlsym(RTLD_NEXT, "free"));
}
static bool performance_enabled_ = false;
static void* (*sys_malloc)(size_t) = 0;
static void* (*sys_realloc)(void*,size_t) = 0;
static void* (*sys_calloc)(size_t,size_t) = 0;
static void (*sys_free)(void*) = 0;
 
static void initialize_functions()
{	
	sys_malloc = reinterpret_cast<void*(*)(size_t)>(dlsym(RTLD_NEXT, "malloc"));
	sys_realloc = reinterpret_cast<void*(*)(void*,size_t)>(dlsym(RTLD_NEXT, "realloc"));
	sys_calloc = reinterpret_cast<void*(*)(size_t,size_t)>(dlsym(RTLD_NEXT, "calloc"));
	sys_free = reinterpret_cast<void(*)(void*)>(dlsym(RTLD_NEXT, "free"));
}

char tmpbuff[1024];
unsigned long tmppos = 0；
unsigned long tmpallocs = 0;
static __thread bool is_external = true;
extern "C" void* malloc(size_t size)
{
	static bool is_initializing = false;
	if(sys_malloc == 0)
	{
		if(!is_initializing)
		{
			is_initializing = true;
			initialize_functions();
			is_initializing = false;
		}
		else
		{
			if(tmppos+size<sizeof(tmpbuff))
			{
				void *retptr = tmpbuff + tmppos;
				tmppos += size;
				++tmpallocs;
				return retptr;
			}
			else
				exit(1);
		}
	}
	void* ptr = sys_malloc(size);
	if(is_external)
	{
		is_external=false;
		handle extra behaviors....
		is_external=true;
	}
	return ptr；
}
