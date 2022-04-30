"# Trick3DEngine" 

The important difference between SEventSystem & FEvent versus TEvent & TDelegate:
	
	SEventSystem & FEvent:
		Event system singleton class contains and manages event queue.
		
		+ Works only with class instances, but singletons also can have static instances.
		+ Event notification can be stopped by changing event status 'IsHandled' to 'true'.
		- Uses std::multimap for listener registry, element access has O(log N) complexity and might be slow with a huge amounts of subscribers.
		- Event subscribers have to inherit from IEventListener and implement its interface (OnEvent(const FEvent* const Event)).
		- In OnEvent function every subscriber have to dispatch events by type using switch statement to appropriate functions.
		- Notification order depends only on subscribition order and can not be changed at runtime.
		

	TEvent & TDelegate:
		Events are self sufficient, event system operates only like a namespace. Easy schaduling for multithreading.
		
		+ Uses std::vector for subscribers list which is faster than map to iterate through, expected to be faster for huge amounts of subscribers.
		+ Easy to use, callback functions can be assigned to the event directly, no switch statements needed.
		+ Callback invocation order can be changed at runtime.
		- Currently works only with static functions which means singletons only;
		- Currently event callback invocation for every subscriber can not be stopped, event have no status.