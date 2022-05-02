"# Trick3DEngine" 

FEvent versus TEvent & TDelegate and important difference between them:
	
	FEvent:

		Event system singleton class contains and manages event queue.
		
		+ Works only with class instances, but singletons also can have static instances.
		+ Event notification can be stopped by changing event status 'IsHandled' to 'true'.
		+ Listener can unsubscribe from all events at once by calling UnsubscribeFromAll(LISTENER);

		- Uses std::multimap for listener registry, element access has O(log N) complexity
		  and might be slow with a huge amounts of subscribers.
		- Event subscribers have to inherit from IEventListener and implement its interface (OnEvent(const FEvent* const Event)).
		- In OnEvent function every subscriber have to dispatch events by type using switch statement to appropriate functions.
		- Notification order depends only on subscribition order and can not be changed at runtime.
		

	TEvent & TDelegate:

		Events are self sufficient, event system operates only like a namespace. Easy schaduling for multithreading.
		
		+ Uses std::vector for subscribers list which is faster than map to iterate through,
		  expected to be faster for huge amounts of subscribers.
		+ Easy to use, callback functions can be assigned to the event directly with '+=' operator, no switch statements needed.
		+ Callback invocation order can be changed at runtime.
		+ Event callbacks has to have a bool8 type and this should be interpreted as
		  'Continue invocation?' where 'return true' means 'Yes' and 'return false' means 'No'.

		- Currently works with static functions only which means - singletons only;
		- Currently subscriber have to manually unsubscribe from each event it has been subscribed on.

Seems like TEvent & TDelegate are usefull only for some specific cases, wherever SEventSystem is suitable for everything.