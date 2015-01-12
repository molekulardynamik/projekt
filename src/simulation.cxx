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

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "simulation.hxx"

// type_t
// 

const type_t::sigma_type& type_t::
sigma () const
{
  return this->sigma_.get ();
}

type_t::sigma_type& type_t::
sigma ()
{
  return this->sigma_.get ();
}

void type_t::
sigma (const sigma_type& x)
{
  this->sigma_.set (x);
}

type_t::sigma_type type_t::
sigma_default_value ()
{
  return sigma_type (0.0);
}

const type_t::epsilon_type& type_t::
epsilon () const
{
  return this->epsilon_.get ();
}

type_t::epsilon_type& type_t::
epsilon ()
{
  return this->epsilon_.get ();
}

void type_t::
epsilon (const epsilon_type& x)
{
  this->epsilon_.set (x);
}

type_t::epsilon_type type_t::
epsilon_default_value ()
{
  return epsilon_type (0.0);
}

const type_t::mass_type& type_t::
mass () const
{
  return this->mass_.get ();
}

type_t::mass_type& type_t::
mass ()
{
  return this->mass_.get ();
}

void type_t::
mass (const mass_type& x)
{
  this->mass_.set (x);
}

type_t::mass_type type_t::
mass_default_value ()
{
  return mass_type (0.0);
}


// vec3i_t
// 

const vec3i_t::X_type& vec3i_t::
X () const
{
  return this->X_.get ();
}

vec3i_t::X_type& vec3i_t::
X ()
{
  return this->X_.get ();
}

void vec3i_t::
X (const X_type& x)
{
  this->X_.set (x);
}

vec3i_t::X_type vec3i_t::
X_default_value ()
{
  return X_type (0);
}

const vec3i_t::Y_type& vec3i_t::
Y () const
{
  return this->Y_.get ();
}

vec3i_t::Y_type& vec3i_t::
Y ()
{
  return this->Y_.get ();
}

void vec3i_t::
Y (const Y_type& x)
{
  this->Y_.set (x);
}

vec3i_t::Y_type vec3i_t::
Y_default_value ()
{
  return Y_type (0);
}

const vec3i_t::Z_type& vec3i_t::
Z () const
{
  return this->Z_.get ();
}

vec3i_t::Z_type& vec3i_t::
Z ()
{
  return this->Z_.get ();
}

void vec3i_t::
Z (const Z_type& x)
{
  this->Z_.set (x);
}

vec3i_t::Z_type vec3i_t::
Z_default_value ()
{
  return Z_type (0);
}


// vec3d_t
// 

const vec3d_t::X_type& vec3d_t::
X () const
{
  return this->X_.get ();
}

vec3d_t::X_type& vec3d_t::
X ()
{
  return this->X_.get ();
}

void vec3d_t::
X (const X_type& x)
{
  this->X_.set (x);
}

vec3d_t::X_type vec3d_t::
X_default_value ()
{
  return X_type (0.0);
}

const vec3d_t::Y_type& vec3d_t::
Y () const
{
  return this->Y_.get ();
}

vec3d_t::Y_type& vec3d_t::
Y ()
{
  return this->Y_.get ();
}

void vec3d_t::
Y (const Y_type& x)
{
  this->Y_.set (x);
}

vec3d_t::Y_type vec3d_t::
Y_default_value ()
{
  return Y_type (0.0);
}

const vec3d_t::Z_type& vec3d_t::
Z () const
{
  return this->Z_.get ();
}

vec3d_t::Z_type& vec3d_t::
Z ()
{
  return this->Z_.get ();
}

void vec3d_t::
Z (const Z_type& x)
{
  this->Z_.set (x);
}

vec3d_t::Z_type vec3d_t::
Z_default_value ()
{
  return Z_type (0.0);
}


// cuboid_t
// 

const cuboid_t::position_type& cuboid_t::
position () const
{
  return this->position_.get ();
}

cuboid_t::position_type& cuboid_t::
position ()
{
  return this->position_.get ();
}

void cuboid_t::
position (const position_type& x)
{
  this->position_.set (x);
}

void cuboid_t::
position (::std::auto_ptr< position_type > x)
{
  this->position_.set (x);
}

const cuboid_t::initialVelocity_type& cuboid_t::
initialVelocity () const
{
  return this->initialVelocity_.get ();
}

cuboid_t::initialVelocity_type& cuboid_t::
initialVelocity ()
{
  return this->initialVelocity_.get ();
}

void cuboid_t::
initialVelocity (const initialVelocity_type& x)
{
  this->initialVelocity_.set (x);
}

void cuboid_t::
initialVelocity (::std::auto_ptr< initialVelocity_type > x)
{
  this->initialVelocity_.set (x);
}

const cuboid_t::particleCount_type& cuboid_t::
particleCount () const
{
  return this->particleCount_.get ();
}

cuboid_t::particleCount_type& cuboid_t::
particleCount ()
{
  return this->particleCount_.get ();
}

void cuboid_t::
particleCount (const particleCount_type& x)
{
  this->particleCount_.set (x);
}

void cuboid_t::
particleCount (::std::auto_ptr< particleCount_type > x)
{
  this->particleCount_.set (x);
}

const cuboid_t::spacing_type& cuboid_t::
spacing () const
{
  return this->spacing_.get ();
}

cuboid_t::spacing_type& cuboid_t::
spacing ()
{
  return this->spacing_.get ();
}

void cuboid_t::
spacing (const spacing_type& x)
{
  this->spacing_.set (x);
}

const cuboid_t::type_type& cuboid_t::
type () const
{
  return this->type_.get ();
}

cuboid_t::type_type& cuboid_t::
type ()
{
  return this->type_.get ();
}

void cuboid_t::
type (const type_type& x)
{
  this->type_.set (x);
}

cuboid_t::type_type cuboid_t::
type_default_value ()
{
  return type_type (0);
}


// sphere_t
// 

const sphere_t::type_type& sphere_t::
type () const
{
  return this->type_.get ();
}

sphere_t::type_type& sphere_t::
type ()
{
  return this->type_.get ();
}

void sphere_t::
type (const type_type& x)
{
  this->type_.set (x);
}

const sphere_t::position_type& sphere_t::
position () const
{
  return this->position_.get ();
}

sphere_t::position_type& sphere_t::
position ()
{
  return this->position_.get ();
}

void sphere_t::
position (const position_type& x)
{
  this->position_.set (x);
}

void sphere_t::
position (::std::auto_ptr< position_type > x)
{
  this->position_.set (x);
}

const sphere_t::initialVelocity_type& sphere_t::
initialVelocity () const
{
  return this->initialVelocity_.get ();
}

sphere_t::initialVelocity_type& sphere_t::
initialVelocity ()
{
  return this->initialVelocity_.get ();
}

void sphere_t::
initialVelocity (const initialVelocity_type& x)
{
  this->initialVelocity_.set (x);
}

void sphere_t::
initialVelocity (::std::auto_ptr< initialVelocity_type > x)
{
  this->initialVelocity_.set (x);
}

const sphere_t::radius_type& sphere_t::
radius () const
{
  return this->radius_.get ();
}

sphere_t::radius_type& sphere_t::
radius ()
{
  return this->radius_.get ();
}

void sphere_t::
radius (const radius_type& x)
{
  this->radius_.set (x);
}

const sphere_t::spacing_type& sphere_t::
spacing () const
{
  return this->spacing_.get ();
}

sphere_t::spacing_type& sphere_t::
spacing ()
{
  return this->spacing_.get ();
}

void sphere_t::
spacing (const spacing_type& x)
{
  this->spacing_.set (x);
}


// simulation_t
// 

const simulation_t::domain_type& simulation_t::
domain () const
{
  return this->domain_.get ();
}

simulation_t::domain_type& simulation_t::
domain ()
{
  return this->domain_.get ();
}

void simulation_t::
domain (const domain_type& x)
{
  this->domain_.set (x);
}

void simulation_t::
domain (::std::auto_ptr< domain_type > x)
{
  this->domain_.set (x);
}

const simulation_t::rCutOf_type& simulation_t::
rCutOf () const
{
  return this->rCutOf_.get ();
}

simulation_t::rCutOf_type& simulation_t::
rCutOf ()
{
  return this->rCutOf_.get ();
}

void simulation_t::
rCutOf (const rCutOf_type& x)
{
  this->rCutOf_.set (x);
}

const simulation_t::type_sequence& simulation_t::
type () const
{
  return this->type_;
}

simulation_t::type_sequence& simulation_t::
type ()
{
  return this->type_;
}

void simulation_t::
type (const type_sequence& s)
{
  this->type_ = s;
}

const simulation_t::cuboid_sequence& simulation_t::
cuboid () const
{
  return this->cuboid_;
}

simulation_t::cuboid_sequence& simulation_t::
cuboid ()
{
  return this->cuboid_;
}

void simulation_t::
cuboid (const cuboid_sequence& s)
{
  this->cuboid_ = s;
}

const simulation_t::sphere_sequence& simulation_t::
sphere () const
{
  return this->sphere_;
}

simulation_t::sphere_sequence& simulation_t::
sphere ()
{
  return this->sphere_;
}

void simulation_t::
sphere (const sphere_sequence& s)
{
  this->sphere_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// type_t
//

type_t::
type_t ()
: ::xml_schema::type (),
  sigma_ (sigma_default_value (), ::xml_schema::flags (), this),
  epsilon_ (epsilon_default_value (), ::xml_schema::flags (), this),
  mass_ (mass_default_value (), ::xml_schema::flags (), this)
{
}

type_t::
type_t (const type_t& x,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  sigma_ (x.sigma_, f, this),
  epsilon_ (x.epsilon_, f, this),
  mass_ (x.mass_, f, this)
{
}

type_t::
type_t (const ::xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  sigma_ (f, this),
  epsilon_ (f, this),
  mass_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
    this->parse (p, f);
  }
}

void type_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "sigma" && n.namespace_ ().empty ())
    {
      this->sigma_.set (sigma_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "epsilon" && n.namespace_ ().empty ())
    {
      this->epsilon_.set (epsilon_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "mass" && n.namespace_ ().empty ())
    {
      this->mass_.set (mass_traits::create (i, f, this));
      continue;
    }
  }

  if (!sigma_.present ())
  {
    this->sigma_.set (sigma_default_value ());
  }

  if (!epsilon_.present ())
  {
    this->epsilon_.set (epsilon_default_value ());
  }

  if (!mass_.present ())
  {
    this->mass_.set (mass_default_value ());
  }
}

type_t* type_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class type_t (*this, f, c);
}

type_t::
~type_t ()
{
}

// vec3i_t
//

vec3i_t::
vec3i_t ()
: ::xml_schema::type (),
  X_ (X_default_value (), ::xml_schema::flags (), this),
  Y_ (Y_default_value (), ::xml_schema::flags (), this),
  Z_ (Z_default_value (), ::xml_schema::flags (), this)
{
}

vec3i_t::
vec3i_t (const vec3i_t& x,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  X_ (x.X_, f, this),
  Y_ (x.Y_, f, this),
  Z_ (x.Z_, f, this)
{
}

vec3i_t::
vec3i_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  X_ (f, this),
  Y_ (f, this),
  Z_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
    this->parse (p, f);
  }
}

void vec3i_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "X" && n.namespace_ ().empty ())
    {
      this->X_.set (X_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "Y" && n.namespace_ ().empty ())
    {
      this->Y_.set (Y_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "Z" && n.namespace_ ().empty ())
    {
      this->Z_.set (Z_traits::create (i, f, this));
      continue;
    }
  }

  if (!X_.present ())
  {
    this->X_.set (X_default_value ());
  }

  if (!Y_.present ())
  {
    this->Y_.set (Y_default_value ());
  }

  if (!Z_.present ())
  {
    this->Z_.set (Z_default_value ());
  }
}

vec3i_t* vec3i_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class vec3i_t (*this, f, c);
}

vec3i_t::
~vec3i_t ()
{
}

// vec3d_t
//

vec3d_t::
vec3d_t ()
: ::xml_schema::type (),
  X_ (X_default_value (), ::xml_schema::flags (), this),
  Y_ (Y_default_value (), ::xml_schema::flags (), this),
  Z_ (Z_default_value (), ::xml_schema::flags (), this)
{
}

vec3d_t::
vec3d_t (const vec3d_t& x,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  X_ (x.X_, f, this),
  Y_ (x.Y_, f, this),
  Z_ (x.Z_, f, this)
{
}

vec3d_t::
vec3d_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  X_ (f, this),
  Y_ (f, this),
  Z_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
    this->parse (p, f);
  }
}

void vec3d_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "X" && n.namespace_ ().empty ())
    {
      this->X_.set (X_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "Y" && n.namespace_ ().empty ())
    {
      this->Y_.set (Y_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "Z" && n.namespace_ ().empty ())
    {
      this->Z_.set (Z_traits::create (i, f, this));
      continue;
    }
  }

  if (!X_.present ())
  {
    this->X_.set (X_default_value ());
  }

  if (!Y_.present ())
  {
    this->Y_.set (Y_default_value ());
  }

  if (!Z_.present ())
  {
    this->Z_.set (Z_default_value ());
  }
}

vec3d_t* vec3d_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class vec3d_t (*this, f, c);
}

vec3d_t::
~vec3d_t ()
{
}

// cuboid_t
//

cuboid_t::
cuboid_t (const position_type& position,
          const initialVelocity_type& initialVelocity,
          const particleCount_type& particleCount,
          const spacing_type& spacing)
: ::xml_schema::type (),
  position_ (position, ::xml_schema::flags (), this),
  initialVelocity_ (initialVelocity, ::xml_schema::flags (), this),
  particleCount_ (particleCount, ::xml_schema::flags (), this),
  spacing_ (spacing, ::xml_schema::flags (), this),
  type_ (type_default_value (), ::xml_schema::flags (), this)
{
}

cuboid_t::
cuboid_t (::std::auto_ptr< position_type >& position,
          ::std::auto_ptr< initialVelocity_type >& initialVelocity,
          ::std::auto_ptr< particleCount_type >& particleCount,
          const spacing_type& spacing)
: ::xml_schema::type (),
  position_ (position, ::xml_schema::flags (), this),
  initialVelocity_ (initialVelocity, ::xml_schema::flags (), this),
  particleCount_ (particleCount, ::xml_schema::flags (), this),
  spacing_ (spacing, ::xml_schema::flags (), this),
  type_ (type_default_value (), ::xml_schema::flags (), this)
{
}

cuboid_t::
cuboid_t (const cuboid_t& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  position_ (x.position_, f, this),
  initialVelocity_ (x.initialVelocity_, f, this),
  particleCount_ (x.particleCount_, f, this),
  spacing_ (x.spacing_, f, this),
  type_ (x.type_, f, this)
{
}

cuboid_t::
cuboid_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  position_ (f, this),
  initialVelocity_ (f, this),
  particleCount_ (f, this),
  spacing_ (f, this),
  type_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
    this->parse (p, f);
  }
}

void cuboid_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // position
    //
    if (n.name () == "position" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< position_type > r (
        position_traits::create (i, f, this));

      if (!position_.present ())
      {
        this->position_.set (r);
        continue;
      }
    }

    // initialVelocity
    //
    if (n.name () == "initialVelocity" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< initialVelocity_type > r (
        initialVelocity_traits::create (i, f, this));

      if (!initialVelocity_.present ())
      {
        this->initialVelocity_.set (r);
        continue;
      }
    }

    // particleCount
    //
    if (n.name () == "particleCount" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< particleCount_type > r (
        particleCount_traits::create (i, f, this));

      if (!particleCount_.present ())
      {
        this->particleCount_.set (r);
        continue;
      }
    }

    // spacing
    //
    if (n.name () == "spacing" && n.namespace_ ().empty ())
    {
      if (!spacing_.present ())
      {
        this->spacing_.set (spacing_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!position_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "position",
      "");
  }

  if (!initialVelocity_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "initialVelocity",
      "");
  }

  if (!particleCount_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "particleCount",
      "");
  }

  if (!spacing_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "spacing",
      "");
  }

  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "type" && n.namespace_ ().empty ())
    {
      this->type_.set (type_traits::create (i, f, this));
      continue;
    }
  }

  if (!type_.present ())
  {
    this->type_.set (type_default_value ());
  }
}

cuboid_t* cuboid_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class cuboid_t (*this, f, c);
}

cuboid_t::
~cuboid_t ()
{
}

// sphere_t
//

sphere_t::
sphere_t (const type_type& type,
          const position_type& position,
          const initialVelocity_type& initialVelocity,
          const radius_type& radius,
          const spacing_type& spacing)
: ::xml_schema::type (),
  type_ (type, ::xml_schema::flags (), this),
  position_ (position, ::xml_schema::flags (), this),
  initialVelocity_ (initialVelocity, ::xml_schema::flags (), this),
  radius_ (radius, ::xml_schema::flags (), this),
  spacing_ (spacing, ::xml_schema::flags (), this)
{
}

sphere_t::
sphere_t (const type_type& type,
          ::std::auto_ptr< position_type >& position,
          ::std::auto_ptr< initialVelocity_type >& initialVelocity,
          const radius_type& radius,
          const spacing_type& spacing)
: ::xml_schema::type (),
  type_ (type, ::xml_schema::flags (), this),
  position_ (position, ::xml_schema::flags (), this),
  initialVelocity_ (initialVelocity, ::xml_schema::flags (), this),
  radius_ (radius, ::xml_schema::flags (), this),
  spacing_ (spacing, ::xml_schema::flags (), this)
{
}

sphere_t::
sphere_t (const sphere_t& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  type_ (x.type_, f, this),
  position_ (x.position_, f, this),
  initialVelocity_ (x.initialVelocity_, f, this),
  radius_ (x.radius_, f, this),
  spacing_ (x.spacing_, f, this)
{
}

sphere_t::
sphere_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  type_ (f, this),
  position_ (f, this),
  initialVelocity_ (f, this),
  radius_ (f, this),
  spacing_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void sphere_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // type
    //
    if (n.name () == "type" && n.namespace_ ().empty ())
    {
      if (!type_.present ())
      {
        this->type_.set (type_traits::create (i, f, this));
        continue;
      }
    }

    // position
    //
    if (n.name () == "position" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< position_type > r (
        position_traits::create (i, f, this));

      if (!position_.present ())
      {
        this->position_.set (r);
        continue;
      }
    }

    // initialVelocity
    //
    if (n.name () == "initialVelocity" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< initialVelocity_type > r (
        initialVelocity_traits::create (i, f, this));

      if (!initialVelocity_.present ())
      {
        this->initialVelocity_.set (r);
        continue;
      }
    }

    // radius
    //
    if (n.name () == "radius" && n.namespace_ ().empty ())
    {
      if (!radius_.present ())
      {
        this->radius_.set (radius_traits::create (i, f, this));
        continue;
      }
    }

    // spacing
    //
    if (n.name () == "spacing" && n.namespace_ ().empty ())
    {
      if (!spacing_.present ())
      {
        this->spacing_.set (spacing_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!type_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "type",
      "");
  }

  if (!position_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "position",
      "");
  }

  if (!initialVelocity_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "initialVelocity",
      "");
  }

  if (!radius_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "radius",
      "");
  }

  if (!spacing_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "spacing",
      "");
  }
}

sphere_t* sphere_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class sphere_t (*this, f, c);
}

sphere_t::
~sphere_t ()
{
}

// simulation_t
//

simulation_t::
simulation_t (const domain_type& domain,
              const rCutOf_type& rCutOf)
: ::xml_schema::type (),
  domain_ (domain, ::xml_schema::flags (), this),
  rCutOf_ (rCutOf, ::xml_schema::flags (), this),
  type_ (::xml_schema::flags (), this),
  cuboid_ (::xml_schema::flags (), this),
  sphere_ (::xml_schema::flags (), this)
{
}

simulation_t::
simulation_t (::std::auto_ptr< domain_type >& domain,
              const rCutOf_type& rCutOf)
: ::xml_schema::type (),
  domain_ (domain, ::xml_schema::flags (), this),
  rCutOf_ (rCutOf, ::xml_schema::flags (), this),
  type_ (::xml_schema::flags (), this),
  cuboid_ (::xml_schema::flags (), this),
  sphere_ (::xml_schema::flags (), this)
{
}

simulation_t::
simulation_t (const simulation_t& x,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  domain_ (x.domain_, f, this),
  rCutOf_ (x.rCutOf_, f, this),
  type_ (x.type_, f, this),
  cuboid_ (x.cuboid_, f, this),
  sphere_ (x.sphere_, f, this)
{
}

simulation_t::
simulation_t (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  domain_ (f, this),
  rCutOf_ (f, this),
  type_ (f, this),
  cuboid_ (f, this),
  sphere_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void simulation_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // domain
    //
    if (n.name () == "domain" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< domain_type > r (
        domain_traits::create (i, f, this));

      if (!domain_.present ())
      {
        this->domain_.set (r);
        continue;
      }
    }

    // rCutOf
    //
    if (n.name () == "rCutOf" && n.namespace_ ().empty ())
    {
      if (!rCutOf_.present ())
      {
        this->rCutOf_.set (rCutOf_traits::create (i, f, this));
        continue;
      }
    }

    // type
    //
    if (n.name () == "type" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< type_type > r (
        type_traits::create (i, f, this));

      this->type_.push_back (r);
      continue;
    }

    // cuboid
    //
    if (n.name () == "cuboid" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< cuboid_type > r (
        cuboid_traits::create (i, f, this));

      this->cuboid_.push_back (r);
      continue;
    }

    // sphere
    //
    if (n.name () == "sphere" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< sphere_type > r (
        sphere_traits::create (i, f, this));

      this->sphere_.push_back (r);
      continue;
    }

    break;
  }

  if (!domain_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "domain",
      "");
  }

  if (!rCutOf_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "rCutOf",
      "");
  }
}

simulation_t* simulation_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class simulation_t (*this, f, c);
}

simulation_t::
~simulation_t ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& u,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& u,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (const ::std::string& u,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::simulation (isrc, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::simulation (isrc, h, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::simulation (isrc, h, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::simulation (isrc, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::simulation (isrc, h, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::std::istream& is,
            const ::std::string& sid,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::simulation (isrc, h, f, p);
}

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& i,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& i,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (::xercesc::InputSource& i,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::simulation_t > r (
    ::simulation (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::simulation_t >
simulation (const ::xercesc::DOMDocument& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::simulation_t > r (
      ::simulation (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "simulation" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::simulation_t > r (
      ::xsd::cxx::tree::traits< ::simulation_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "simulation",
    "");
}

::std::auto_ptr< ::simulation_t >
simulation (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "simulation" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::simulation_t > r (
      ::xsd::cxx::tree::traits< ::simulation_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "simulation",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
