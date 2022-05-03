"# Trick3DEngine" 

SEventSystem versus TEvent & TDelegate and important difference between them:
	
	SEventSystem:

		Singleton class contains and manages event queue.
		
		+ Works only with class instances, but singletons also can have static instances.
		+ Event notification can be stopped by changing event status 'IsHandled' to 'true'.
		+ Listener can unsubscribe from all events at once by calling UnsubscribeFromAll(LISTENER);

		- Since all events are in the same queue, multithreading implementation could be complicated.
		  Each listener has to implement its own multithreading to make things easier.
		- Uses std::multimap for listener registry, element search has O(log N) complexity
		  and might be slow with a huge amounts of subscribers.
		- Event subscribers have to inherit from IEventListener and implement its interface (OnEvent(const FEvent* const Event)).
		- In OnEvent function every subscriber have to dispatch events by type using switch statement to appropriate functions.
		- Notification order depends only on subscribition order and can not be changed at runtime.
		

	TEvent & TDelegate:

		Events are self sufficient.
		
		+ Each event can be processed by a dedicated thread apart from the others.
		  Listeners also could have their own multithreading at the same time.
		+ Uses std::vector for subscribers list which is faster than map to iterate through,
		  expected to be faster for huge amounts of subscribers.
		+ Easy to use, callback functions can be assigned to the event directly, no switch statements needed.
		+ Callback invocation order can be changed at runtime.
		+ Event callbacks has to have a bool8 type and this should be interpreted as
		  'Continue invocation?' where 'return true' means 'Yes' and 'return false' means 'No'.
		+ Supports static functions with instance pointer as a parameter which instance can be accessed through.

		- Subscriber have to manually unsubscribe from each event it has been subscribed on.
		  UnsubscribeFromAll like function is too expensive operation for TEvent & TDelegate.

TEvent & TDelegate now belongs to SEvent static class.
