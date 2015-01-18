// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef SIMULATION_H
#define SIMULATION_H

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3030000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

#include <xsd/cxx/xml/dom/serialization-header.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/serialization/byte.hxx>
#include <xsd/cxx/tree/serialization/unsigned-byte.hxx>
#include <xsd/cxx/tree/serialization/short.hxx>
#include <xsd/cxx/tree/serialization/unsigned-short.hxx>
#include <xsd/cxx/tree/serialization/int.hxx>
#include <xsd/cxx/tree/serialization/unsigned-int.hxx>
#include <xsd/cxx/tree/serialization/long.hxx>
#include <xsd/cxx/tree/serialization/unsigned-long.hxx>
#include <xsd/cxx/tree/serialization/boolean.hxx>
#include <xsd/cxx/tree/serialization/float.hxx>
#include <xsd/cxx/tree/serialization/double.hxx>
#include <xsd/cxx/tree/serialization/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  // Namespace information and list stream. Used in
  // serialization functions.
  //
  typedef ::xsd::cxx::xml::dom::namespace_info< char > namespace_info;
  typedef ::xsd::cxx::xml::dom::namespace_infomap< char > namespace_infomap;
  typedef ::xsd::cxx::tree::list_stream< char > list_stream;
  typedef ::xsd::cxx::tree::as_double< double_ > as_double;
  typedef ::xsd::cxx::tree::as_decimal< decimal > as_decimal;
  typedef ::xsd::cxx::tree::facet facet;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;
  typedef ::xsd::cxx::tree::serialization< char > serialization;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class type_t;
class vec3i_t;
class vec3d_t;
class cuboid_t;
class sphere_t;
class particle_t;
class particleArray_t;
class thermostat_t;
class simulation_t;

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class type_t: public ::xml_schema::type
{
  public:
  // sigma
  // 
  typedef ::xml_schema::double_ sigma_type;
  typedef ::xsd::cxx::tree::traits< sigma_type, char, ::xsd::cxx::tree::schema_type::double_ > sigma_traits;

  const sigma_type&
  sigma () const;

  sigma_type&
  sigma ();

  void
  sigma (const sigma_type& x);

  static sigma_type
  sigma_default_value ();

  // epsilon
  // 
  typedef ::xml_schema::double_ epsilon_type;
  typedef ::xsd::cxx::tree::traits< epsilon_type, char, ::xsd::cxx::tree::schema_type::double_ > epsilon_traits;

  const epsilon_type&
  epsilon () const;

  epsilon_type&
  epsilon ();

  void
  epsilon (const epsilon_type& x);

  static epsilon_type
  epsilon_default_value ();

  // mass
  // 
  typedef ::xml_schema::double_ mass_type;
  typedef ::xsd::cxx::tree::traits< mass_type, char, ::xsd::cxx::tree::schema_type::double_ > mass_traits;

  const mass_type&
  mass () const;

  mass_type&
  mass ();

  void
  mass (const mass_type& x);

  static mass_type
  mass_default_value ();

  // Constructors.
  //
  type_t ();

  type_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  type_t (const type_t& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual type_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~type_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< sigma_type > sigma_;
  ::xsd::cxx::tree::one< epsilon_type > epsilon_;
  ::xsd::cxx::tree::one< mass_type > mass_;
};

class vec3i_t: public ::xml_schema::type
{
  public:
  // X
  // 
  typedef ::xml_schema::int_ X_type;
  typedef ::xsd::cxx::tree::traits< X_type, char > X_traits;

  const X_type&
  X () const;

  X_type&
  X ();

  void
  X (const X_type& x);

  static X_type
  X_default_value ();

  // Y
  // 
  typedef ::xml_schema::int_ Y_type;
  typedef ::xsd::cxx::tree::traits< Y_type, char > Y_traits;

  const Y_type&
  Y () const;

  Y_type&
  Y ();

  void
  Y (const Y_type& x);

  static Y_type
  Y_default_value ();

  // Z
  // 
  typedef ::xml_schema::int_ Z_type;
  typedef ::xsd::cxx::tree::traits< Z_type, char > Z_traits;

  const Z_type&
  Z () const;

  Z_type&
  Z ();

  void
  Z (const Z_type& x);

  static Z_type
  Z_default_value ();

  // Constructors.
  //
  vec3i_t ();

  vec3i_t (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  vec3i_t (const vec3i_t& x,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  virtual vec3i_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~vec3i_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< X_type > X_;
  ::xsd::cxx::tree::one< Y_type > Y_;
  ::xsd::cxx::tree::one< Z_type > Z_;
};

class vec3d_t: public ::xml_schema::type
{
  public:
  // X
  // 
  typedef ::xml_schema::double_ X_type;
  typedef ::xsd::cxx::tree::traits< X_type, char, ::xsd::cxx::tree::schema_type::double_ > X_traits;

  const X_type&
  X () const;

  X_type&
  X ();

  void
  X (const X_type& x);

  static X_type
  X_default_value ();

  // Y
  // 
  typedef ::xml_schema::double_ Y_type;
  typedef ::xsd::cxx::tree::traits< Y_type, char, ::xsd::cxx::tree::schema_type::double_ > Y_traits;

  const Y_type&
  Y () const;

  Y_type&
  Y ();

  void
  Y (const Y_type& x);

  static Y_type
  Y_default_value ();

  // Z
  // 
  typedef ::xml_schema::double_ Z_type;
  typedef ::xsd::cxx::tree::traits< Z_type, char, ::xsd::cxx::tree::schema_type::double_ > Z_traits;

  const Z_type&
  Z () const;

  Z_type&
  Z ();

  void
  Z (const Z_type& x);

  static Z_type
  Z_default_value ();

  // Constructors.
  //
  vec3d_t ();

  vec3d_t (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  vec3d_t (const vec3d_t& x,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  virtual vec3d_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~vec3d_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< X_type > X_;
  ::xsd::cxx::tree::one< Y_type > Y_;
  ::xsd::cxx::tree::one< Z_type > Z_;
};

class cuboid_t: public ::xml_schema::type
{
  public:
  // position
  // 
  typedef ::vec3d_t position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // initialVelocity
  // 
  typedef ::vec3d_t initialVelocity_type;
  typedef ::xsd::cxx::tree::traits< initialVelocity_type, char > initialVelocity_traits;

  const initialVelocity_type&
  initialVelocity () const;

  initialVelocity_type&
  initialVelocity ();

  void
  initialVelocity (const initialVelocity_type& x);

  void
  initialVelocity (::std::auto_ptr< initialVelocity_type > p);

  // particleCount
  // 
  typedef ::vec3i_t particleCount_type;
  typedef ::xsd::cxx::tree::traits< particleCount_type, char > particleCount_traits;

  const particleCount_type&
  particleCount () const;

  particleCount_type&
  particleCount ();

  void
  particleCount (const particleCount_type& x);

  void
  particleCount (::std::auto_ptr< particleCount_type > p);

  // spacing
  // 
  typedef ::xml_schema::double_ spacing_type;
  typedef ::xsd::cxx::tree::traits< spacing_type, char, ::xsd::cxx::tree::schema_type::double_ > spacing_traits;

  const spacing_type&
  spacing () const;

  spacing_type&
  spacing ();

  void
  spacing (const spacing_type& x);

  // type
  // 
  typedef ::xml_schema::int_ type_type;
  typedef ::xsd::cxx::tree::traits< type_type, char > type_traits;

  const type_type&
  type () const;

  type_type&
  type ();

  void
  type (const type_type& x);

  static type_type
  type_default_value ();

  // Constructors.
  //
  cuboid_t (const position_type&,
            const initialVelocity_type&,
            const particleCount_type&,
            const spacing_type&);

  cuboid_t (::std::auto_ptr< position_type >&,
            ::std::auto_ptr< initialVelocity_type >&,
            ::std::auto_ptr< particleCount_type >&,
            const spacing_type&);

  cuboid_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  cuboid_t (const cuboid_t& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual cuboid_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~cuboid_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< initialVelocity_type > initialVelocity_;
  ::xsd::cxx::tree::one< particleCount_type > particleCount_;
  ::xsd::cxx::tree::one< spacing_type > spacing_;
  ::xsd::cxx::tree::one< type_type > type_;
};

class sphere_t: public ::xml_schema::type
{
  public:
  // type
  // 
  typedef ::xml_schema::int_ type_type;
  typedef ::xsd::cxx::tree::traits< type_type, char > type_traits;

  const type_type&
  type () const;

  type_type&
  type ();

  void
  type (const type_type& x);

  // position
  // 
  typedef ::vec3d_t position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // initialVelocity
  // 
  typedef ::vec3d_t initialVelocity_type;
  typedef ::xsd::cxx::tree::traits< initialVelocity_type, char > initialVelocity_traits;

  const initialVelocity_type&
  initialVelocity () const;

  initialVelocity_type&
  initialVelocity ();

  void
  initialVelocity (const initialVelocity_type& x);

  void
  initialVelocity (::std::auto_ptr< initialVelocity_type > p);

  // radius
  // 
  typedef ::xml_schema::int_ radius_type;
  typedef ::xsd::cxx::tree::traits< radius_type, char > radius_traits;

  const radius_type&
  radius () const;

  radius_type&
  radius ();

  void
  radius (const radius_type& x);

  // spacing
  // 
  typedef ::xml_schema::double_ spacing_type;
  typedef ::xsd::cxx::tree::traits< spacing_type, char, ::xsd::cxx::tree::schema_type::double_ > spacing_traits;

  const spacing_type&
  spacing () const;

  spacing_type&
  spacing ();

  void
  spacing (const spacing_type& x);

  // Constructors.
  //
  sphere_t (const type_type&,
            const position_type&,
            const initialVelocity_type&,
            const radius_type&,
            const spacing_type&);

  sphere_t (const type_type&,
            ::std::auto_ptr< position_type >&,
            ::std::auto_ptr< initialVelocity_type >&,
            const radius_type&,
            const spacing_type&);

  sphere_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  sphere_t (const sphere_t& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual sphere_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~sphere_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< type_type > type_;
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< initialVelocity_type > initialVelocity_;
  ::xsd::cxx::tree::one< radius_type > radius_;
  ::xsd::cxx::tree::one< spacing_type > spacing_;
};

class particle_t: public ::xml_schema::type
{
  public:
  // position
  // 
  typedef ::vec3d_t position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // velocity
  // 
  typedef ::vec3d_t velocity_type;
  typedef ::xsd::cxx::tree::traits< velocity_type, char > velocity_traits;

  const velocity_type&
  velocity () const;

  velocity_type&
  velocity ();

  void
  velocity (const velocity_type& x);

  void
  velocity (::std::auto_ptr< velocity_type > p);

  // type
  // 
  typedef ::xml_schema::int_ type_type;
  typedef ::xsd::cxx::tree::optional< type_type > type_optional;
  typedef ::xsd::cxx::tree::traits< type_type, char > type_traits;

  const type_optional&
  type () const;

  type_optional&
  type ();

  void
  type (const type_type& x);

  void
  type (const type_optional& x);

  // Constructors.
  //
  particle_t (const position_type&,
              const velocity_type&);

  particle_t (::std::auto_ptr< position_type >&,
              ::std::auto_ptr< velocity_type >&);

  particle_t (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  particle_t (const particle_t& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  virtual particle_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~particle_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< velocity_type > velocity_;
  type_optional type_;
};

class particleArray_t: public ::xml_schema::type
{
  public:
  // particle
  // 
  typedef ::particle_t particle_type;
  typedef ::xsd::cxx::tree::sequence< particle_type > particle_sequence;
  typedef particle_sequence::iterator particle_iterator;
  typedef particle_sequence::const_iterator particle_const_iterator;
  typedef ::xsd::cxx::tree::traits< particle_type, char > particle_traits;

  const particle_sequence&
  particle () const;

  particle_sequence&
  particle ();

  void
  particle (const particle_sequence& s);

  // Constructors.
  //
  particleArray_t ();

  particleArray_t (const ::xercesc::DOMElement& e,
                   ::xml_schema::flags f = 0,
                   ::xml_schema::container* c = 0);

  particleArray_t (const particleArray_t& x,
                   ::xml_schema::flags f = 0,
                   ::xml_schema::container* c = 0);

  virtual particleArray_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~particleArray_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  particle_sequence particle_;
};

class thermostat_t: public ::xml_schema::type
{
  public:
  // numDimensions
  // 
  typedef ::xml_schema::int_ numDimensions_type;
  typedef ::xsd::cxx::tree::traits< numDimensions_type, char > numDimensions_traits;

  const numDimensions_type&
  numDimensions () const;

  numDimensions_type&
  numDimensions ();

  void
  numDimensions (const numDimensions_type& x);

  // initialTemp
  // 
  typedef ::xml_schema::double_ initialTemp_type;
  typedef ::xsd::cxx::tree::traits< initialTemp_type, char, ::xsd::cxx::tree::schema_type::double_ > initialTemp_traits;

  const initialTemp_type&
  initialTemp () const;

  initialTemp_type&
  initialTemp ();

  void
  initialTemp (const initialTemp_type& x);

  // targetTemp
  // 
  typedef ::xml_schema::double_ targetTemp_type;
  typedef ::xsd::cxx::tree::traits< targetTemp_type, char, ::xsd::cxx::tree::schema_type::double_ > targetTemp_traits;

  const targetTemp_type&
  targetTemp () const;

  targetTemp_type&
  targetTemp ();

  void
  targetTemp (const targetTemp_type& x);

  // step
  // 
  typedef ::xml_schema::int_ step_type;
  typedef ::xsd::cxx::tree::traits< step_type, char > step_traits;

  const step_type&
  step () const;

  step_type&
  step ();

  void
  step (const step_type& x);

  // startTime
  // 
  typedef ::xml_schema::int_ startTime_type;
  typedef ::xsd::cxx::tree::traits< startTime_type, char > startTime_traits;

  const startTime_type&
  startTime () const;

  startTime_type&
  startTime ();

  void
  startTime (const startTime_type& x);

  // targetTime
  // 
  typedef ::xml_schema::int_ targetTime_type;
  typedef ::xsd::cxx::tree::traits< targetTime_type, char > targetTime_traits;

  const targetTime_type&
  targetTime () const;

  targetTime_type&
  targetTime ();

  void
  targetTime (const targetTime_type& x);

  // Constructors.
  //
  thermostat_t (const numDimensions_type&,
                const initialTemp_type&,
                const targetTemp_type&,
                const step_type&,
                const startTime_type&,
                const targetTime_type&);

  thermostat_t (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  thermostat_t (const thermostat_t& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual thermostat_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~thermostat_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< numDimensions_type > numDimensions_;
  ::xsd::cxx::tree::one< initialTemp_type > initialTemp_;
  ::xsd::cxx::tree::one< targetTemp_type > targetTemp_;
  ::xsd::cxx::tree::one< step_type > step_;
  ::xsd::cxx::tree::one< startTime_type > startTime_;
  ::xsd::cxx::tree::one< targetTime_type > targetTime_;
};

class simulation_t: public ::xml_schema::type
{
  public:
  // thermostat
  // 
  typedef ::thermostat_t thermostat_type;
  typedef ::xsd::cxx::tree::traits< thermostat_type, char > thermostat_traits;

  const thermostat_type&
  thermostat () const;

  thermostat_type&
  thermostat ();

  void
  thermostat (const thermostat_type& x);

  void
  thermostat (::std::auto_ptr< thermostat_type > p);

  // gravity
  // 
  typedef ::xml_schema::double_ gravity_type;
  typedef ::xsd::cxx::tree::traits< gravity_type, char, ::xsd::cxx::tree::schema_type::double_ > gravity_traits;

  const gravity_type&
  gravity () const;

  gravity_type&
  gravity ();

  void
  gravity (const gravity_type& x);

  // domain
  // 
  typedef ::vec3d_t domain_type;
  typedef ::xsd::cxx::tree::traits< domain_type, char > domain_traits;

  const domain_type&
  domain () const;

  domain_type&
  domain ();

  void
  domain (const domain_type& x);

  void
  domain (::std::auto_ptr< domain_type > p);

  // boundaries
  // 
  typedef ::vec3i_t boundaries_type;
  typedef ::xsd::cxx::tree::traits< boundaries_type, char > boundaries_traits;

  const boundaries_type&
  boundaries () const;

  boundaries_type&
  boundaries ();

  void
  boundaries (const boundaries_type& x);

  void
  boundaries (::std::auto_ptr< boundaries_type > p);

  // wallType
  // 
  typedef ::xml_schema::int_ wallType_type;
  typedef ::xsd::cxx::tree::traits< wallType_type, char > wallType_traits;

  const wallType_type&
  wallType () const;

  wallType_type&
  wallType ();

  void
  wallType (const wallType_type& x);

  // rCutOff
  // 
  typedef ::xml_schema::float_ rCutOff_type;
  typedef ::xsd::cxx::tree::traits< rCutOff_type, char > rCutOff_traits;

  const rCutOff_type&
  rCutOff () const;

  rCutOff_type&
  rCutOff ();

  void
  rCutOff (const rCutOff_type& x);

  // type
  // 
  typedef ::type_t type_type;
  typedef ::xsd::cxx::tree::sequence< type_type > type_sequence;
  typedef type_sequence::iterator type_iterator;
  typedef type_sequence::const_iterator type_const_iterator;
  typedef ::xsd::cxx::tree::traits< type_type, char > type_traits;

  const type_sequence&
  type () const;

  type_sequence&
  type ();

  void
  type (const type_sequence& s);

  // cuboid
  // 
  typedef ::cuboid_t cuboid_type;
  typedef ::xsd::cxx::tree::sequence< cuboid_type > cuboid_sequence;
  typedef cuboid_sequence::iterator cuboid_iterator;
  typedef cuboid_sequence::const_iterator cuboid_const_iterator;
  typedef ::xsd::cxx::tree::traits< cuboid_type, char > cuboid_traits;

  const cuboid_sequence&
  cuboid () const;

  cuboid_sequence&
  cuboid ();

  void
  cuboid (const cuboid_sequence& s);

  // sphere
  // 
  typedef ::sphere_t sphere_type;
  typedef ::xsd::cxx::tree::sequence< sphere_type > sphere_sequence;
  typedef sphere_sequence::iterator sphere_iterator;
  typedef sphere_sequence::const_iterator sphere_const_iterator;
  typedef ::xsd::cxx::tree::traits< sphere_type, char > sphere_traits;

  const sphere_sequence&
  sphere () const;

  sphere_sequence&
  sphere ();

  void
  sphere (const sphere_sequence& s);

  // particles
  // 
  typedef ::particleArray_t particles_type;
  typedef ::xsd::cxx::tree::optional< particles_type > particles_optional;
  typedef ::xsd::cxx::tree::traits< particles_type, char > particles_traits;

  const particles_optional&
  particles () const;

  particles_optional&
  particles ();

  void
  particles (const particles_type& x);

  void
  particles (const particles_optional& x);

  void
  particles (::std::auto_ptr< particles_type > p);

  // Constructors.
  //
  simulation_t (const thermostat_type&,
                const gravity_type&,
                const domain_type&,
                const boundaries_type&,
                const wallType_type&,
                const rCutOff_type&);

  simulation_t (::std::auto_ptr< thermostat_type >&,
                const gravity_type&,
                ::std::auto_ptr< domain_type >&,
                ::std::auto_ptr< boundaries_type >&,
                const wallType_type&,
                const rCutOff_type&);

  simulation_t (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  simulation_t (const simulation_t& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual simulation_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~simulation_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< thermostat_type > thermostat_;
  ::xsd::cxx::tree::one< gravity_type > gravity_;
  ::xsd::cxx::tree::one< domain_type > domain_;
  ::xsd::cxx::tree::one< boundaries_type > boundaries_;
  ::xsd::cxx::tree::one< wallType_type > wallType_;
  ::xsd::cxx::tree::one< rCutOff_type > rCutOff_;
  type_sequence type_;
  cuboid_sequence cuboid_;
  sphere_sequence sphere_;
  particles_optional particles_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& uri,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& uri,
            ::xml_schema::error_handler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& uri,
            ::xercesc::DOMErrorHandler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xml_schema::error_handler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xercesc::DOMErrorHandler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& id,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& id,
            ::xml_schema::error_handler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& id,
            ::xercesc::DOMErrorHandler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& is,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& is,
            ::xml_schema::error_handler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& is,
            ::xercesc::DOMErrorHandler& eh,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::auto_ptr< ::simulation_t >
simulation (const ::xercesc::DOMDocument& d,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::simulation_t >
simulation (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
            ::xml_schema::flags f = 0,
            const ::xml_schema::properties& p = ::xml_schema::properties ());

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

void
operator<< (::xercesc::DOMElement&, const type_t&);

void
operator<< (::xercesc::DOMElement&, const vec3i_t&);

void
operator<< (::xercesc::DOMElement&, const vec3d_t&);

void
operator<< (::xercesc::DOMElement&, const cuboid_t&);

void
operator<< (::xercesc::DOMElement&, const sphere_t&);

void
operator<< (::xercesc::DOMElement&, const particle_t&);

void
operator<< (::xercesc::DOMElement&, const particleArray_t&);

void
operator<< (::xercesc::DOMElement&, const thermostat_t&);

void
operator<< (::xercesc::DOMElement&, const simulation_t&);

// Serialize to std::ostream.
//

void
simulation (::std::ostream& os,
            const ::simulation_t& x, 
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

void
simulation (::std::ostream& os,
            const ::simulation_t& x, 
            ::xml_schema::error_handler& eh,
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

void
simulation (::std::ostream& os,
            const ::simulation_t& x, 
            ::xercesc::DOMErrorHandler& eh,
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

// Serialize to xercesc::XMLFormatTarget.
//

void
simulation (::xercesc::XMLFormatTarget& ft,
            const ::simulation_t& x, 
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

void
simulation (::xercesc::XMLFormatTarget& ft,
            const ::simulation_t& x, 
            ::xml_schema::error_handler& eh,
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

void
simulation (::xercesc::XMLFormatTarget& ft,
            const ::simulation_t& x, 
            ::xercesc::DOMErrorHandler& eh,
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            const ::std::string& e = "UTF-8",
            ::xml_schema::flags f = 0);

// Serialize to an existing xercesc::DOMDocument.
//

void
simulation (::xercesc::DOMDocument& d,
            const ::simulation_t& x,
            ::xml_schema::flags f = 0);

// Serialize to a new xercesc::DOMDocument.
//

::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
simulation (const ::simulation_t& x, 
            const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
            ::xml_schema::flags f = 0);

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // SIMULATION_H
