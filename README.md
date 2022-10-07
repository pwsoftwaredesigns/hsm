# Hierarchical State Machine (HSM) Framework for C++

**pw::hsm** is an implementation of UML statecharts/HSM written for C++.
It provides a framework for writing object-oriented state machines where each
state is represented by its own class.  Most operations (e.g., transitions) use
constexpr and templates.

## Features

* Each state represented by a class
* Helper macros to simplify creation of boiler-plate code
* Can operate without heal (i.e., malloc) using 
	[ETL](https://github.com/ETLCPP/etl) pools. This is useful for embedded
	systems.
	
## Basic Example

Helper macros have been provided to further smilify writing of a state machine
and states


First, forward-declare your states and state machine.

```cmake
class MyStateMachine;
class RootState;
class State1;
class State11;
class State12;
```

Second, use a macro to defined "traits" for you state machine.  This includes
all the events you state machine will handle.

```cmake
PW_HSM_STATE_MACHINE_TRAITS(
	MyStateMachine, 
	RootState,
	(Event1),
	(Event2)
);
```

Next, define your states

> ***Note:*** States **must** be defined in **reverse-order** when using
memory pools otherwise the application will not compile.  This is because the
parent state must have the **complete** definiton of all its children in order
to create a pool containing them.

```cmake
PW_HSM_STATE(MyStateMachine, State11, State1)
{
public:
	State11(parent_type& parent) :
		State(parent)
	{
		//Your "enter" actions should be placed in the constructor
	}
	
	~State11() {
		//Your "exit" actions should be placed in the destructor
	}
	
public:
	::pw::hsm::return_type visit(const Event1& e) override { 
		/*
		* Return pw::HSM::PASS to indicate that this state has NOT fully handled
		* this event.  The event WILL be passed upwards to the parent state.
		*/
		return PASS;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override {
		/*
		* Return pw::HSM::HANDLED to indicate that this state has fully handled
		* this event.  The event will NOT be passed upwards to the parent state
		* once it has been handled.
		*/
		return pw::HSM::HANDLED;
	}
};

PW_HSM_STATE(MyStateMachine, State12, State1)
{
	//See body of State11
};

/*
* After defining the state machine, name of the state, and parent,
* the remaining (optional) arguemnts to PW_HSM_STATE are the names of this 
* state's children.
*/
PW_HSM_STATE(MyStateMachine, State1, RootState, State11, State12)
{
	//See body of State11
};

//The "root" has the state machine itself as its parent
PW_HSM_STATE(MyStateMachine, RootState, MyStateMachine, State1)
{
	//See body of State11
};
```

Finally, define the state machine.

```cmake
PW_HSM_STATE_MACHINE(MyStateMachine) {
public:
	MyStateMachine()
	{
		/*
		* The state machine could contain public variables or methods used
		* as context (i.e., extended state variables) that is common to all 
		* states
		*/
	}
};
```

You can use you state machine as follows.

```cmake
Event1 e1;
Event2 e2;

MyStateMachine sm;

//Perform the initial transition into the deepest leaf state
sm.init();

sm.dispatch(e1);
sm.dispatch(e2);

sm.deinit();
```

> ***Note:*** Because your actual state classes inherit from the template State,
but the implementation is contained within this subclass, you need to call
deinit() to "exit" states in the correct order.

## Building the project

**pw::hsm** is a header-only (template) library that can be included into any
c++ project.

### Prerequisites

* **C++ compiler**
* **make** - To build examples using makefile

In addition, the `lib` folder contains submodule dependencies of this project.

### Compilation Options

It does provide a few compilation
option macros listed below:

* **PW_HSM_USE_ETL** - If set to 1, etl::pool/variant_pool are used to allocate/
	create states rather than std::make_unique.
* **PW_HSM_PASS_TRACE** - Trace each time PASS is returned from an event handler
* **PW_HSM_HANDLED_TRACE** - Trace each time HANDLED is returned from an event 
	handler
* **PW_HSM_TRANSITION_TRACE(src, dest)** - Trace state transitions from src to
	dest
                
## Testing

Testing and development have been perform on the following platforms:

* GNU G++, C++17, Windows 10, x64

## Authors

* **Patrick Wright** - [@pwsoftwaredesigns](https://github.com/pwsoftwaredesigns)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

See https://github.com/filipdutescu/modern-cpp-template for README template