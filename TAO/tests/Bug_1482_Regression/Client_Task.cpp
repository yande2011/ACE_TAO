//
// $Id$
//

#include "Client_Task.h"
#include "tao/Stub.h"

ACE_RCSID(Muxing, Client_Task, "$Id$")

Client_Task::Client_Task (Test::Hello_ptr receiver,
                          CORBA::ORB_ptr o,
                          ACE_Thread_Manager *thr_mgr)
  : ACE_Task_Base (thr_mgr)
    , receiver_ (Test::Hello::_duplicate (receiver))
    , handler_ (o)
    , handler_var_ ()
    , orb_ (CORBA::ORB::_duplicate (o))
{
  this->handler_var_ = this->handler_._this ();
  this->handler_var_->_stubobj ()->_incr_refcnt ();
  this->handler_var_->_add_ref ();
}

Client_Task::~Client_Task (void)
{
  (void) this->handler_var_._retn ();
}

int
Client_Task::svc (void)
{
  // ACE_DEBUG ((LM_DEBUG, "(%P|%t) Starting client task\n"));

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      for (CORBA::Long j = 0;
           j != 1000;
           ++j)
        {
          // Send 25 messages in every loop..
          for (CORBA::Short i = 0; i != 25; ++i)
            {
              this->receiver_->sendc_next_prime (this->handler_var_.in ()
                                                 ACE_ENV_ARG_PARAMETER);
              ACE_TRY_CHECK;
            }

          CORBA::Short repl = 0;
          CORBA::Long tries = 0;

          ACE_Time_Value tv (1, 1);

          /// No scientific underpinning for the number 10000.
          while (repl != 25 && tries != 10000)
            {
              CORBA::Boolean pending =
                this->orb_->work_pending (ACE_ENV_SINGLE_ARG_PARAMETER);
              ACE_TRY_CHECK;

              if (pending)
                {
                  this->orb_->perform_work (tv
                                            ACE_ENV_ARG_PARAMETER);
                  ACE_TRY_CHECK;
                  ++repl;

                  // Reset tries here since we have a reply.
                  tries = 0;
                }

              ++tries;
            }
        }
    }
  ACE_CATCHANY
    {
      return -1;
    }
  ACE_ENDTRY;
  ACE_DEBUG ((LM_DEBUG, "(%P|%t) Client task finished\n"));
  return 0;
}
