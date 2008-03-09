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

#ifndef CIAO_SENDER_EXEC_H
#define CIAO_SENDER_EXEC_H

#include /**/ "ace/pre.h"

#include "SenderEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "Sender_exec_export.h"
#include "tao/LocalObject.h"

namespace CIDL_Sender_Impl
{
  /**
   * @class Sender_exec_i
   *
   * Sender executor implementation class.
   */
  class SENDER_EXEC_Export Sender_exec_i
    : public virtual Sender_Exec,
      public virtual TAO_Local_RefCounted_Object
  {

  public:
    /// Default constructor.
    Sender_exec_i ()
      : message_(CORBA::string_dup ("Default Message")),
        color_ (::Hello::empty)
    {
    }

    /// Secondary construction.
    Sender_exec_i (const char* local_message)
      : message_ (CORBA::string_dup (local_message)),
        color_ (::Hello::empty)
    {
    }

    /// Default destructor.
    virtual ~Sender_exec_i ();

    /// Operation to set the value of the attribute "local_message"
    virtual void local_message (const char * local_message);

    /// Operation to get the value of the attribute "local_message"
    virtual char * local_message ();

    /// Operation to set the value of the attribute "hertz"
    virtual void hertz (CORBA::Long hertz);

    /// Operation to get the value of the attribute "hertz"
    virtual CORBA::Long hertz ();

    /* Operations for obtaining the interface reference. */
    /* This method will be used in the assembly face so the
     * ObjRef of this read_message facet will be sent to the
     * client side(receptacle).
     */
    // Note: You can specify the return type as ::Hello::CCM_message *
    virtual ::Hello::CCM_ReadMessage_ptr
    get_push_message ();

    virtual ::Hello::COLOR_SELECTION
    color ();

    virtual void
    color (::Hello::COLOR_SELECTION);

    // Operation inside of the trigger interface.
    virtual void start ();

    // Operations from Components::SessionComponent
    virtual void set_session_context (::Components::SessionContext_ptr ctx);

    virtual void ciao_preactivate ();

    virtual void ccm_activate ();

    virtual void ciao_postactivate ();

    virtual void ccm_passivate ();

    virtual void ccm_remove ();

  protected:
    /// Copmponent specific context
    ::Hello::CCM_Sender_Context_var context_;

  private:
    CORBA::String_var message_;

    CORBA::Long hertz_;

    ::Hello::COLOR_SELECTION color_;

    friend class Message_Impl;
  };


  //
  //
  //
  class Message_Impl : public virtual Hello::CCM_ReadMessage,
                       public virtual TAO_Local_RefCounted_Object
  {
  public:
    Message_Impl (Sender_exec_i& component)
        : component_ (component)
    {
    }

    virtual char *
    get_message ();

  private:
    Sender_exec_i& component_;
  };

  /**
   * @class SenderHome_exec_i
   *
   * Sender home executor implementation class.
   */
  class SENDER_EXEC_Export SenderHome_exec_i
    : public virtual SenderHome_Exec,
      public virtual TAO_Local_RefCounted_Object
  {
    public:
    SenderHome_exec_i (void);
    virtual ~SenderHome_exec_i (void);

    // Supported or inherited operations.

    // Home operations.

    // Factory and finder operations.

    // Attribute operations.

    // Implicit operations.

    virtual ::Components::EnterpriseComponent_ptr
    create ();
  };
  
  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent
    create_Hello_Sender_Impl (void);

  extern "C" SENDER_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_Hello_SenderHome_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* CIAO_SENDER_EXEC_H */
