#include "ChatRoom.h"

Person* ChatRoom::PersonReference::operator->() const
{
	return &people[index];
}

void ChatRoom::broadcast(const std::string& origin, const std::string& message)
{
	for (auto& person : people)
	{
		if (person.name != origin)
		{
			person.receive(origin, message);
		}
	}
}

ChatRoom::PersonReference ChatRoom::join(Person&& p)
{
	const std::string join_message = p.name + " joins the chat";
	broadcast("room", join_message);

	p.room = this;
	people.emplace_back(p);
	return { people, people.size() - 1 };
}

void ChatRoom::message(const std::string& origin, const std::string& who, const std::string& message)
{
	auto target = find_if(begin(people), end(people),
		[&](const Person& p) { return p.name == who; });
	if (target != end(people))
	{
		target->receive(origin, message);
	}
}
