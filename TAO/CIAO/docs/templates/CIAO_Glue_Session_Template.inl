// $Id$ -*- C++ -*-

//    The generated filename for files using this template shoule be
//       [idl-basename]GS.i        GS --> GlueSession

// @@ Notice: [ciao module name] can expand to either CIAO_GLUE or
//    CIAO_GLUE_[module name] as defined in the header file.

//////////////////////////////////////////////////////////////////
// Facet Glue Code implementation
// @@ We are assuming that these facets are declared under the same
//    module as the component (thus, we are placing this glue code
//    here under the same namespace.  If they are not, we will
//    either be generating them in separate namespaces, or include
//    some other CIDL generated files to get the glue code
//    implementation.
//////////////////////////////////////////////////////////////////

##foreach [facet type] in (all facet interface types in the original IDL)
// Constructor and destructor.
ACE_INLINE
[ciao module name]::[facet type]_Servant::[facet type]_Servant (CCM_[facet type]_ptr executor,
                                                                ::Components::CCMContext_ptr c)
  : executor_ (CCM_[facet type]::_duplicate (executor)),
    ctx_ (c)
{
}

ACE_INLINE
[ciao module name]::[facet type]_Servant::~[facet tyep]_Servant ()
{
}


##  foreach [operation] in (all facet operations)

// This is only a guideline...  we always relay the operation to underlying
// executor.

ACE_INLINE [operation return_type]
[ciao module name]::[facet type]_Servant::[operation] ([operation args])
{
  // Simply relay to executor.  May not need to return the result...
  return this->executor_->operation ([operation args]);
}
##  end foreach [operation]

##end foreach [facet type]


//////////////////////////////////////////////////////////////////
// Component specific context implementation
//////////////////////////////////////////////////////////////////

ACE_INLINE
[ciao module name]::[component name]_Context::[component name]_Context (::Components::CCMHome_ptr home,
                                                                        ::CIAO::Session_Container *c,
                                                                        [component name]_Servant *sv)
  : home_ (::Components::CCMHome::_duplicate (h)),
    container_ (c),
    servant_ (sv)
{

}

ACE_INLINE
[ciao module name]::[component name]_Context::~[component name]_Context ()
{
}

##foreach [receptacle name] with [uses type] in (list of all 'uses' interfaces) generate:

##  if [receptacle name] is a simplex receptacle ('uses')

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Context::get_connection_[receptacle name] (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return [uses type]::_duplicate (this->ciao_uses_[receptacle name]_.in ());
}

// Simplex [receptacle name] connection management operations
ACE_INLINE void
[ciao module name]::[component name]_Context::connect_[receptacle name] ([uses type]_ptr c
                                                                         ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::AlreadyConnected,
                   ::Components::InvalidConnection))
{
  if (! CORBA::is_nil (this->ciao_uses_[receptacle name]_.in ()))
    ACE_THROW (::Components::AlreadyConnected ());

  // When do we throw InvalidConnection exception?
  this->ciao_uses_[receptacle name]_ = [uses type]::_duplicate (c);
}

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Context::disconnect_[receptacle name] ()
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::NoConnection))
{
  if (CORBA::is_nil (this->ciao_uses_[receptacle name]_.in ()))
    ACE_THROW (::Components::NoConnection ());

  return this->ciao_uses_[receptacle name]_.retn ();
}

##  else ([receptacle name] is a multiplex ('uses multiple') receptacle)
// Multiplex [receptacle name] connection management operations
ACE_INLINE ::Components::Cookie_ptr
[ciao module name]::[component name]_Context::connect_[receptacle name] ([uses type]_ptr c)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       ::Components::ExceedConnectionLimit,
                       ::Components::InvalidConnection))
{
  if (CORBA::is_nil (c))
    ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);

  CIAO::Active_Objref_Map::key_type key;
  this->ciao_muses_[receptacle name]_.bind (c,
                                            key);

  ::Components::Cookie_var retv = new CIAO::Map_Key_Cookie (key);
  return retv._retn ();
}

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Context::disconnect_[receptacle name] (::Components::Cookie_ptr ck)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::InvalidConnection))
{
  [uses type]_var retv;

  if (ck == 0 ||
      this->ciao_muses_[receptacle name]_.unbind (ck,
                                                  retv) != 0)
    ACE_THROW_RETURN (::Components::InvalidConnection (), 0);

  return retv._retn ();
}

##  endif [receptacle name]
##end foreach [receptacle name] with [uses type]

// Operations for emits interfaces.
##foreach [emit name] with [eventtype] in (list of all emitters) generate:

ACE_INLINE void
[ciao module name]::[component name]_Context::connect_[emit name] ([eventtype]Consumer_ptr c
                                                                   ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::AlreadyConnected))
{
  if (CORBA::is_nil (c))
    ACE_THROW (CORBA::BAD_PARAM ());

  if (! CORBA::is_nil (this->ciao_emits_[emit name]_consumer_.in ()))
    ACE_THROW (::Components::AlreadyConnected ());

  this->ciao_emits_[emit name]_consumer_ = c;
}

ACE_INLINE [eventtype]Consumer_ptr
[ciao module name]::[component name]_Context::disconnect_[emit name] (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::NoConnection))
{
  if (CORBA::is_nil (this->ciao_emits_[emit name]_consumer_.in ()))
    ACE_THROW (::Components::NoConnection ());

  return this->ciao_emits_[emit name]_consumer_._retn ();
}

##end foreach [emit name] with [eventtype]

    // Operations for publishes interfaces.
##foreach [publish name] with [eventtype] in (list of all publishers) generate:
ACE_INLINE ::Components::Cookie_ptr
[ciao module name]::[component name]_Context::subscribe_[publish name] ([eventtype]Consumer_ptr c
                                                                        ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::ExceededConnectionLimit))
{
  if (CORBA::is_nil (c))
    ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);

  CIAO::Active_Objref_Map::key_type key;
  this->ciao_publishes_[publish name]_map_.bind (c,
                                                 key);

  ::Components::Cookie_var retv = new CIAO::Map_Key_Cookie (key);
  return retv._retn ();
}

ACE_INLINE [eventtype]Consumer_ptr
unsubscribe_[publish name] (::Components::Cookie_ptr ck
                            ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::InvalidConnection));
{
  [eventtype]Consumer_var retv;

  if (ck == 0 ||
      this->ciao_publishes_[publish name]_map_.unbind (ck,
                                                       retv) != 0)
    ACE_THROW_RETURN (::Components::InvalidConnection (), 0);

  return retv._retn ();
}

##end foreach [publish name] with [eventtype]

// Operations for ::Components::CCMContext
ACE_INLINE ::Components::Principal_ptr
[ciao module name]::[component name]_Context::get_caller_principal (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // @@ We don't support Security in CIAO yet.
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

ACE_INLINE ::Components::CCMHome_ptr
[ciao module name]::[component name]_Context::get_CCM_home (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return ::Components::CCMHome::_duplicate (this->home_.in ());
}

ACE_INLINE CORBA::Boolean
[ciao module name]::[component name]_Context::get_rollback_only (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Components::IllegalState))
{
  // @@ We don't support Transaction in CIAO yet.
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

ACE_INLINE ::Components::Transaction::UserTransaction_ptr
[ciao module name]::[component name]_Context::get_user_transaction (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Components::IllegalState))
{
  // @@ We don't support Transaction in CIAO yet.
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

ACE_INLINE CORBA::Boolean
[ciao module name]::[component name]_Context::is_caller_in_role (const char * role
                                                                 ACE_ENV_ARG_DECL)
      ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_UNUSED_ARG (role);

  // @@ We don't support Transaction in CIAO yet.
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

ACE_INLINE void
[ciao module name]::[component name]_Context::set_rollback_only (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Components::IllegalState))
{
  // @@ We don't support Transaction in CIAO yet.
  ACE_THROW (CORBA::NO_IMPLEMENT ());
}

//////////////////////////////////////////////////////////////////
// Component Servant Glue code implementation
//////////////////////////////////////////////////////////////////

ACE_INLINE
[ciao module name]::[component name]_Servant::[component name]_Servant (CCM_[component name]_ptr exe,
                                                                        ::Components::CCMHome_ptr h,
                                                                        ::CIAO::Session_Container *c)
  : executor_ (CCM_[component name]::_duplicate (exe)),
    container_ (c)
{
  this->context_ = new [component name]_Context (h, c, this);
}

ACE_INLINE
[ciao module name]::[component name]_Servant::~[component name]_Servant (void)
{
}

##foreach [operation] in all supported interfaces of own component and all inherited components

// This is only a guideline...  we always relay the operation to underlying
// executor.

ACE_INLINE [operation return_type]
[ciao module name]::[component name]_Servant::[operation] ([operation args])
{
  // Simply relay to executor.  May not need to return the result...
  return this->executor_->operation ([operation args]);
}

##end

##foreach [receptacle name] with [uses type] in (list of all 'uses' interfaces) generate:
##  if [receptacle name] is a simplex receptacle ('uses')
    // Simplex [receptacle name] connection management operations
ACE_INLINE void
[ciao module name]::[component name]_Servant::connect_[receptacle name] ([uses type]_ptr c
                                                                         ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::AlreadyConnected,
                   ::Components::InvalidConnection))
{
  this->context_->connect_[receptacle name] (c ACE_ENV_ARG_PARAMETER);
}

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Servant::disconnect_[receptacle name] (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::NoConnection))
{
  return this->context_->disconnect_[receptacle name] (ACE_ENV_SINGLE_ARG_PARAMETER);
}

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Servant::get_connection_[receptacle name] (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->context_->get_connection_[receptacle name] (ACE_ENV_SINGLE_ARG_PARAMETER);
}
##  else ([receptacle name] is a multiplex ('uses multiple') receptacle)

    // Multiplex [receptacle name] connection management operations
ACE_INLINE ::Components::Cookie_ptr
[ciao module name]::[component name]_Servant::connect_[receptacle name] ([uses type]_ptr c
                                                                         ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::ExceedConnectionLimit,
                   ::Components::InvalidConnection))
{
  return this->context_->connect_[receptacle name] (c
                                                    ACE_ENV_ARG_PARAMETER);
}

ACE_INLINE [uses type]_ptr
[ciao module name]::[component name]_Servant::disconnect_[receptacle name] (::Components::Cookie_ptr ck
                                                                            ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::InvalidConnection))
{
  return this->context_->disconnect_[receptacle name] (ck
                                                       ACE_ENV_ARG_PARAMETER);
}

ACE_INLINE [receptacle name]Connections *
[ciao module name]::[component name]_Servant::get_connections_[receptacle name] (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->context_->get_connections_[receptacle name] (ACE_ENV_SINGLE_ARG_PARAMETER);
}

##  endif [receptacle name]
##end foreach [receptacle name] with [uses type]

//////////////////////////////////////////////////////////////////
// EventConsumer Glue Code implementation
// @@ We are assuming that these consumers are declared under the same
//    module as the component (thus, we are placing this glue code
//    here under the same namespace.  If they are not, we will
//    either be generating them in separate namespaces, or include
//    some other CIDL generated files to get the glue code
//    implementation.
//////////////////////////////////////////////////////////////////

##foreach [consumer name] with [eventtype] in (list of all consumers) generate:

// Constructor and destructor.
ACE_INLINE
[ciao module name]::[component name]_Servant::[event type]Consumer_[consumer name]_Servant::[event type]Consumer_[consumer name]_Servant
  (CCM_[component name]_ptr executor,
   CCM_[component name]_Context_ptr c)
  : executor_ (CCM_[event type]Consumer::_duplicate (executor)),
    ctx_ (CCM_[component name]_Context::_duplicate (c))
{
}

ACE_INLINE
[ciao module name]::[component name]_Servant::[event type]Consumer_[consumer name]_Servant::~[event type]Consumer_[consumer name]_Servant ()
{
}

ACE_INLINE CORBA::Object_ptr
[ciao module name]::[component name]_Servant::[event type]Consumer_[consumer name]_Servant::_get_component (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->ctx_->get_CCM_Object (ACE_ENV_SINGLE_ARG_PARAMETER);
}

ACE_INLINE void
[ciao module name]::[component name]_Servant::[event type]Consumer_[consumer name]_Servant::push_[eventtype]
  ([eventtype]_ptr evt
   ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->executor_->push_[consumer name] (evt ACE_ENV_ARG);
}

##  foreach [type] in (all parents of eventtype, if any, not including EventConsumerBase)
ACE_INLINE void
[ciao module name]::[component name]_Servant::[eventtype]Consumer_[consumer name]_Servant::push_[type]
  ([type]_ptr evt
   ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // @@ Problem, there's no way to handle this case.

  //  this->executor_->push_[consumer name] (evt ACE_ENV_ARG);
  ACE_THROW (::CORBA::BAD_PARAM ());
}
##  end [type]

##end foreach [consumer name]

    // Operations for emits interfaces.
##foreach [emit name] with [eventtype] in (list of all emitters) generate:
ACE_INLINE void
[ciao module name]::[component name]_Servant::connect_[emit name] ([eventtype]Consumer_ptr c
                                                                   ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException
                   ::Components::AlreadyConnected))
{
  this->context_->connect_[emit name] (c
                                       ACE_ENV_ARG_PARAMETER);
}

ACE_INLINE [eventtype]Consumer_ptr
[ciao module name]::[component name]_Servant::disconnect_[emit name] (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::NoConnection))
{
  return this->context_->disconnect_[emit name] (ACE_ENV_SINGLE_ARG_PARAMETER);
}
##end foreach [emit name] with [eventtype]

    // Operations for publishes interfaces.
##foreach [publish name] with [eventtype] in (list of all publishers) generate:
ACE_INLINE ::Components::Cookie_ptr
[ciao module name]::[component name]_Servant::subscribe_[publish name] ([eventtype]Consumer_ptr c
                                                                        ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::ExceededConnectionLimit))
{
  return this->context_->subscribe_[publish name] (c
                                                   ACE_ENV_ARG_PARAMATER);
}

ACE_INLINE [eventtype]Consumer_ptr
[ciao module name]::[component name]_Servant::unsubscribe_[publish name] (::Components::Cookie_ptr ck
                                                                          ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   ::Components::InvalidConnection))
{
  return this->context_->unsubscribe_[publish name] (ck
                                                     ACE_ENV_ARG_PARAMETER);
}
##end foreach [publish name] with [eventtype]
