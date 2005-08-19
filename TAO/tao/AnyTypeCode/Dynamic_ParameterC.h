// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be\be_codegen.cpp:153

#ifndef _TAO_IDL_ORIG_DYNAMIC_PARAMETERC_H_
#define _TAO_IDL_ORIG_DYNAMIC_PARAMETERC_H_

#include /**/ "ace/pre.h"


#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/AnyTypeCode/TAO_AnyTypeCode_Export.h"
#include "tao/ORB.h"
#include "tao/Environment.h"
#include "tao/AnyTypeCode/TypeCode_Constants.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/VarOut_T.h"

#include "tao/ParameterModeC.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_AnyTypeCode_Export

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

// TAO_IDL - Generated from
// be\be_visitor_module/module_ch.cpp:48

namespace Dynamic
{

  // TAO_IDL - Generated from
  // be\be_type.cpp:258

  struct Parameter;

  typedef
    TAO_Var_Var_T<
        Parameter
      >
    Parameter_var;

  typedef
    TAO_Out_T<
        Parameter,
        Parameter_var
      >
    Parameter_out;

  // TAO_IDL - Generated from
  // be\be_visitor_structure/structure_ch.cpp:52

  struct TAO_AnyTypeCode_Export Parameter
  {
    typedef Parameter_var _var_type;

    static void _tao_any_destructor (void *);
    CORBA::Any argument;
    CORBA::ParameterMode mode;
  };

// TAO_IDL - Generated from
// be\be_visitor_module/module_ch.cpp:66

} // module Dynamic

// TAO_IDL - Generated from
// be\be_visitor_traits.cpp:61

// Traits specializations.
namespace TAO
{
}

// TAO_IDL - Generated from
// be\be_visitor_structure/cdr_op_ch.cpp:54

TAO_AnyTypeCode_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const Dynamic::Parameter &);
TAO_AnyTypeCode_Export CORBA::Boolean operator>> (TAO_InputCDR &, Dynamic::Parameter &);

// TAO_IDL - Generated from
// be\be_codegen.cpp:955

#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include /**/ "ace/post.h"

#endif /* ifndef */


