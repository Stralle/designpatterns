/*
	Mediator - a component that facilitates communication between other components without them being aware of each other
	or having direct (referential) access to each other.
*/

#include <iostream>
#include <string>

#include "ChatRoom.h"

// Rename this for testing purposes
int mainChatRoom()
{
	ChatRoom room;

	auto john = room.join(Person{ "John" });
	auto jane = room.join(Person{ "Jane" });

	john->say("Hi room");
	jane->say("Hi John!");

	auto simon = room.join(Person{ "Simon" });
	simon->say("hi everyone!");

	jane->pm("Simon", "glad you could join us, simon");
		
	return 0;
}