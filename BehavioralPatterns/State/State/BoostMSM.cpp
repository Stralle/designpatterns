#include <iostream>
#include <string>
#include <vector>

// Back-end
#include <boost/msm/back/state_machine.hpp>

// Front-end
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

std::vector<std::string> state_names
{
	"off hook", //s
	"connecting",
	"connected",
	"on hold",
	"destroyed"
};

struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
	bool angry{ true }; // Guard. Whether the transition is possible or not.
	
	struct OffHook : state<> {};
	struct Connecting : state<>
	{
		template <class Event, class FSM>
		void on_entry(Event const& evt, FSM&)
		{
			std::cout << "We are connecting..." << std::endl;
		} // on_exit
	};

	struct PhoneBeingDestroyed // functor
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Phone breaks into a million pieces" << std::endl;
		}
	};

	struct CanDestroyPhone // functor
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
		{
			return fsm.angry; // we know that angry is part of the fsm.
		}
	};
	
	struct Connected : state<> {};
	struct OnHold : state<> {};
	struct PhoneDestroyed : state<> {};

	struct transition_table : mpl::vector<
		Row<OffHook, CallDialed, Connecting>,
		Row<Connecting, CallConnected, Connected>,
		Row<Connected, PlacedOnHold, OnHold>,
	//      SOURCE	EVENT				 TARGET			 ACTION				  GUARD
		Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
	>{};

	typedef OffHook initial_state;

	template <class FSM, class Event>
	void no_transition(Event const& e, FSM&, int state)
	{
		std::cout << "No transition from state " << state_names[state] << " on event " << typeid(e).name() << std::endl;
	}
};

// Rename this to main for testing purposes
int main()
{
	msm::back::state_machine<PhoneStateMachine> phone;

	auto info = [&]()
	{
		auto i = phone.current_state()[0];
		std::cout << "The phone is currently " << state_names[i] << "\n";
	};

	info();
	phone.process_event(CallDialed{});
	info();
	phone.process_event(CallConnected{});
	info();
	phone.process_event(PlacedOnHold{});
	info();
	phone.process_event(PhoneThrownIntoWall{});
	info();
	phone.process_event(CallDialed{}); // This can't be done if there's no predefined transition or no_transition.

	return 0;
}