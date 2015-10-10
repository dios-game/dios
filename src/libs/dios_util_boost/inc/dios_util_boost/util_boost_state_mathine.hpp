#ifndef _DIOS_UTIL_BOOST_STATEMACHINE_H__
#define _DIOS_UTIL_BOOST_STATEMACHINE_H__

#include <cassert>
#include <string>

#include "dios_util_boost_lib.h"
#include "dios_util/util_byte_array.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

namespace FSM{
	template <class EntityType>
	class State
	{
	public:
		virtual ~State(){}
		virtual void Enter(EntityType* entity) {}
		virtual void Update(EntityType* entity) {}
		virtual void Update(EntityType* entity, int delta) {}
		virtual void Exit(EntityType* entity) {}
		virtual bool SendMessage(EntityType* entity, const dios::util::CByteArray& message) { return false; }
		virtual bool SendMessage(EntityType* entity, int msg_code, const dios::util::CByteArray& message) { return false; }
	};

	template <class EntityType>
	class StateMachine
	{
	protected:
		EntityType*          owner_;
		State<EntityType>*   current_state_;
		State<EntityType>*   previous_state_;
		State<EntityType>*   global_state_;
		typedef std::function<void(void)> StateChangedCallback;

	public:
		StateMachine(void):owner_(NULL),current_state_(NULL),previous_state_(NULL),global_state_(NULL){}
		StateMachine(EntityType* owner):owner_(owner),current_state_(NULL),previous_state_(NULL),global_state_(NULL){}
		virtual ~StateMachine(){}

		void Init(EntityType* owner) {
			owner_ = owner;
		}

		void Update(void)const
		{
			if(global_state_)  global_state_->Update(owner_);
			if(current_state_) current_state_->Update(owner_);
		}

		void Update(int delta)const
		{
			if(global_state_)  global_state_->Update(owner_, delta);
			if(current_state_) current_state_->Update(owner_, delta);
		}

		/*
		*	同一状态机对象切换返回false
		*/
		bool ChangeState(State<EntityType>* new_state, const StateChangedCallback& state_changed_callback=StateChangedCallback())
		{
			previous_state_ = current_state_;
			if(current_state_) current_state_->Exit(owner_);
			current_state_ = new_state;
			if(state_changed_callback) state_changed_callback();
			if(current_state_) current_state_->Enter(owner_);
			return true;
		}

		bool SendMessage(const dios::util::CByteArray& message)
		{
			if( !current_state_ || !current_state_->SendMessage(owner_, message))
			{
				if(global_state_) {
					return global_state_->SendMessage(owner_, message);
				}
			}
			return false;
		}

		bool SendMessage(int msg_code, const dios::util::CByteArray& message)
		{
			if( !current_state_ || !current_state_->SendMessage(owner_, msg_code, message))
			{
				if(global_state_) {
					return global_state_->SendMessage(owner_, msg_code, message);
				}
			}
			return false;
		}

		void RevertToPreviousState(){ ChangeState(previous_state_); }

		void set_current_state(State<EntityType>* s){ current_state_ = s; }
		void set_global_state(State<EntityType>* s) { global_state_ = s; }
		void set_previous_state(State<EntityType>* s){ previous_state_ = s; }

		State<EntityType>*  current_state()  const{ return current_state_; }
		State<EntityType>*  global_state()   const{ return global_state_; }
		State<EntityType>*  previous_state() const{ return previous_state_; }
	};
}

NS_UTIL_BOOST_END
NS_DS_END

#endif


