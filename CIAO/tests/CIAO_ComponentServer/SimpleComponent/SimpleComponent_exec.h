// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#ifndef CIAO_SIMPLECOMPONENT_EXEC_H
#define CIAO_SIMPLECOMPONENT_EXEC_H

#include /**/ "ace/pre.h"

#include "SimpleComponentEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "SimpleComponent_exec_export.h"
#include "tao/LocalObject.h"

namespace CIDL_SimpleComponent_Impl
{
  class SIMPLECOMPONENT_EXEC_Export SimpleComponent_exec_i
    : public virtual Simple_Exec,
      public virtual ::CORBA::LocalObject
  {
    public:
    SimpleComponent_exec_i (const char *CreateType);
    virtual ~SimpleComponent_exec_i (void);

    // Supported or inherited operations.

    virtual void
    trigger ();

    // Attribute operations.

    virtual char *
    creationtype_ ()
    ;

    // Port operations.

    // Operations from Components::SessionComponent

    virtual void
    set_session_context (
      ::Components::SessionContext_ptr ctx);

    virtual void configuration_complete ();

    virtual void ccm_activate ();

    virtual void ccm_passivate ();

    virtual void ccm_remove ();

    private:
    ::Foo::CCM_SimpleComponent_Context_var context_;

    CORBA::String_var type_;

  };

  class SIMPLECOMPONENT_EXEC_Export SimpleHome_exec_i
    : public virtual SimpleComponent_Exec,
      public virtual ::CORBA::LocalObject
  {
    public:
    SimpleHome_exec_i (void);
    virtual ~SimpleHome_exec_i (void);

    // Supported or inherited operations.

    // Home operations.

    // Factory and finder operations.

    // Attribute operations.

    // Implicit operations.

    virtual ::Components::EnterpriseComponent_ptr
    create ();
  };

  extern "C" SIMPLECOMPONENT_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_Foo_SimpleHome_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* CIAO_SIMPLECOMPONENT_EXEC_H */
