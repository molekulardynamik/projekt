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

#include "config.h"

// statistics_t
// 

const statistics_t::filename_type& statistics_t::
filename () const
{
  return this->filename_.get ();
}

statistics_t::filename_type& statistics_t::
filename ()
{
  return this->filename_.get ();
}

void statistics_t::
filename (const filename_type& x)
{
  this->filename_.set (x);
}

void statistics_t::
filename (::std::auto_ptr< filename_type > x)
{
  this->filename_.set (x);
}

const statistics_t::filename_type& statistics_t::
filename_default_value ()
{
  return filename_default_value_;
}

const statistics_t::iterations_type& statistics_t::
iterations () const
{
  return this->iterations_.get ();
}

statistics_t::iterations_type& statistics_t::
iterations ()
{
  return this->iterations_.get ();
}

void statistics_t::
iterations (const iterations_type& x)
{
  this->iterations_.set (x);
}

statistics_t::iterations_type statistics_t::
iterations_default_value ()
{
  return iterations_type (100000);
}


// output_t
// 

const output_t::dir_type& output_t::
dir () const
{
  return this->dir_.get ();
}

output_t::dir_type& output_t::
dir ()
{
  return this->dir_.get ();
}

void output_t::
dir (const dir_type& x)
{
  this->dir_.set (x);
}

void output_t::
dir (::std::auto_ptr< dir_type > x)
{
  this->dir_.set (x);
}

const output_t::filename_type& output_t::
filename () const
{
  return this->filename_.get ();
}

output_t::filename_type& output_t::
filename ()
{
  return this->filename_.get ();
}

void output_t::
filename (const filename_type& x)
{
  this->filename_.set (x);
}

void output_t::
filename (::std::auto_ptr< filename_type > x)
{
  this->filename_.set (x);
}

const output_t::iterations_type& output_t::
iterations () const
{
  return this->iterations_.get ();
}

output_t::iterations_type& output_t::
iterations ()
{
  return this->iterations_.get ();
}

void output_t::
iterations (const iterations_type& x)
{
  this->iterations_.set (x);
}

const output_t::velocityProfile_optional& output_t::
velocityProfile () const
{
  return this->velocityProfile_;
}

output_t::velocityProfile_optional& output_t::
velocityProfile ()
{
  return this->velocityProfile_;
}

void output_t::
velocityProfile (const velocityProfile_type& x)
{
  this->velocityProfile_.set (x);
}

void output_t::
velocityProfile (const velocityProfile_optional& x)
{
  this->velocityProfile_ = x;
}

void output_t::
velocityProfile (::std::auto_ptr< velocityProfile_type > x)
{
  this->velocityProfile_.set (x);
}

const output_t::diffusion_optional& output_t::
diffusion () const
{
  return this->diffusion_;
}

output_t::diffusion_optional& output_t::
diffusion ()
{
  return this->diffusion_;
}

void output_t::
diffusion (const diffusion_type& x)
{
  this->diffusion_.set (x);
}

void output_t::
diffusion (const diffusion_optional& x)
{
  this->diffusion_ = x;
}

void output_t::
diffusion (::std::auto_ptr< diffusion_type > x)
{
  this->diffusion_.set (x);
}

const output_t::rdf_optional& output_t::
rdf () const
{
  return this->rdf_;
}

output_t::rdf_optional& output_t::
rdf ()
{
  return this->rdf_;
}

void output_t::
rdf (const rdf_type& x)
{
  this->rdf_.set (x);
}

void output_t::
rdf (const rdf_optional& x)
{
  this->rdf_ = x;
}

void output_t::
rdf (::std::auto_ptr< rdf_type > x)
{
  this->rdf_.set (x);
}


// config_t
// 

const config_t::delta_type& config_t::
delta () const
{
  return this->delta_.get ();
}

config_t::delta_type& config_t::
delta ()
{
  return this->delta_.get ();
}

void config_t::
delta (const delta_type& x)
{
  this->delta_.set (x);
}

const config_t::end_type& config_t::
end () const
{
  return this->end_.get ();
}

config_t::end_type& config_t::
end ()
{
  return this->end_.get ();
}

void config_t::
end (const end_type& x)
{
  this->end_.set (x);
}

const config_t::output_type& config_t::
output () const
{
  return this->output_.get ();
}

config_t::output_type& config_t::
output ()
{
  return this->output_.get ();
}

void config_t::
output (const output_type& x)
{
  this->output_.set (x);
}

void config_t::
output (::std::auto_ptr< output_type > x)
{
  this->output_.set (x);
}

const config_t::simulationFile_type& config_t::
simulationFile () const
{
  return this->simulationFile_.get ();
}

config_t::simulationFile_type& config_t::
simulationFile ()
{
  return this->simulationFile_.get ();
}

void config_t::
simulationFile (const simulationFile_type& x)
{
  this->simulationFile_.set (x);
}

void config_t::
simulationFile (::std::auto_ptr< simulationFile_type > x)
{
  this->simulationFile_.set (x);
}

const config_t::saveFile_optional& config_t::
saveFile () const
{
  return this->saveFile_;
}

config_t::saveFile_optional& config_t::
saveFile ()
{
  return this->saveFile_;
}

void config_t::
saveFile (const saveFile_type& x)
{
  this->saveFile_.set (x);
}

void config_t::
saveFile (const saveFile_optional& x)
{
  this->saveFile_ = x;
}

void config_t::
saveFile (::std::auto_ptr< saveFile_type > x)
{
  this->saveFile_.set (x);
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// statistics_t
//

const statistics_t::filename_type statistics_t::filename_default_value_ (
  "profile");

statistics_t::
statistics_t ()
: ::xml_schema::type (),
  filename_ (filename_default_value (), ::xml_schema::flags (), this),
  iterations_ (iterations_default_value (), ::xml_schema::flags (), this)
{
}

statistics_t::
statistics_t (const statistics_t& x,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  filename_ (x.filename_, f, this),
  iterations_ (x.iterations_, f, this)
{
}

statistics_t::
statistics_t (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  filename_ (f, this),
  iterations_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
    this->parse (p, f);
  }
}

void statistics_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "filename" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< filename_type > r (
        filename_traits::create (i, f, this));

      this->filename_.set (r);
      continue;
    }

    if (n.name () == "iterations" && n.namespace_ ().empty ())
    {
      this->iterations_.set (iterations_traits::create (i, f, this));
      continue;
    }
  }

  if (!filename_.present ())
  {
    this->filename_.set (filename_default_value ());
  }

  if (!iterations_.present ())
  {
    this->iterations_.set (iterations_default_value ());
  }
}

statistics_t* statistics_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class statistics_t (*this, f, c);
}

statistics_t::
~statistics_t ()
{
}

// output_t
//

output_t::
output_t (const dir_type& dir,
          const filename_type& filename,
          const iterations_type& iterations)
: ::xml_schema::type (),
  dir_ (dir, ::xml_schema::flags (), this),
  filename_ (filename, ::xml_schema::flags (), this),
  iterations_ (iterations, ::xml_schema::flags (), this),
  velocityProfile_ (::xml_schema::flags (), this),
  diffusion_ (::xml_schema::flags (), this),
  rdf_ (::xml_schema::flags (), this)
{
}

output_t::
output_t (const output_t& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  dir_ (x.dir_, f, this),
  filename_ (x.filename_, f, this),
  iterations_ (x.iterations_, f, this),
  velocityProfile_ (x.velocityProfile_, f, this),
  diffusion_ (x.diffusion_, f, this),
  rdf_ (x.rdf_, f, this)
{
}

output_t::
output_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  dir_ (f, this),
  filename_ (f, this),
  iterations_ (f, this),
  velocityProfile_ (f, this),
  diffusion_ (f, this),
  rdf_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void output_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // dir
    //
    if (n.name () == "dir" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< dir_type > r (
        dir_traits::create (i, f, this));

      if (!dir_.present ())
      {
        this->dir_.set (r);
        continue;
      }
    }

    // filename
    //
    if (n.name () == "filename" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< filename_type > r (
        filename_traits::create (i, f, this));

      if (!filename_.present ())
      {
        this->filename_.set (r);
        continue;
      }
    }

    // iterations
    //
    if (n.name () == "iterations" && n.namespace_ ().empty ())
    {
      if (!iterations_.present ())
      {
        this->iterations_.set (iterations_traits::create (i, f, this));
        continue;
      }
    }

    // velocityProfile
    //
    if (n.name () == "velocityProfile" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< velocityProfile_type > r (
        velocityProfile_traits::create (i, f, this));

      if (!this->velocityProfile_)
      {
        this->velocityProfile_.set (r);
        continue;
      }
    }

    // diffusion
    //
    if (n.name () == "diffusion" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< diffusion_type > r (
        diffusion_traits::create (i, f, this));

      if (!this->diffusion_)
      {
        this->diffusion_.set (r);
        continue;
      }
    }

    // rdf
    //
    if (n.name () == "rdf" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< rdf_type > r (
        rdf_traits::create (i, f, this));

      if (!this->rdf_)
      {
        this->rdf_.set (r);
        continue;
      }
    }

    break;
  }

  if (!dir_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "dir",
      "");
  }

  if (!filename_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "filename",
      "");
  }

  if (!iterations_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "iterations",
      "");
  }
}

output_t* output_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class output_t (*this, f, c);
}

output_t::
~output_t ()
{
}

// config_t
//

config_t::
config_t (const delta_type& delta,
          const end_type& end,
          const output_type& output,
          const simulationFile_type& simulationFile)
: ::xml_schema::type (),
  delta_ (delta, ::xml_schema::flags (), this),
  end_ (end, ::xml_schema::flags (), this),
  output_ (output, ::xml_schema::flags (), this),
  simulationFile_ (simulationFile, ::xml_schema::flags (), this),
  saveFile_ (::xml_schema::flags (), this)
{
}

config_t::
config_t (const delta_type& delta,
          const end_type& end,
          ::std::auto_ptr< output_type >& output,
          const simulationFile_type& simulationFile)
: ::xml_schema::type (),
  delta_ (delta, ::xml_schema::flags (), this),
  end_ (end, ::xml_schema::flags (), this),
  output_ (output, ::xml_schema::flags (), this),
  simulationFile_ (simulationFile, ::xml_schema::flags (), this),
  saveFile_ (::xml_schema::flags (), this)
{
}

config_t::
config_t (const config_t& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  delta_ (x.delta_, f, this),
  end_ (x.end_, f, this),
  output_ (x.output_, f, this),
  simulationFile_ (x.simulationFile_, f, this),
  saveFile_ (x.saveFile_, f, this)
{
}

config_t::
config_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  delta_ (f, this),
  end_ (f, this),
  output_ (f, this),
  simulationFile_ (f, this),
  saveFile_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void config_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // delta
    //
    if (n.name () == "delta" && n.namespace_ ().empty ())
    {
      if (!delta_.present ())
      {
        this->delta_.set (delta_traits::create (i, f, this));
        continue;
      }
    }

    // end
    //
    if (n.name () == "end" && n.namespace_ ().empty ())
    {
      if (!end_.present ())
      {
        this->end_.set (end_traits::create (i, f, this));
        continue;
      }
    }

    // output
    //
    if (n.name () == "output" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< output_type > r (
        output_traits::create (i, f, this));

      if (!output_.present ())
      {
        this->output_.set (r);
        continue;
      }
    }

    // simulationFile
    //
    if (n.name () == "simulationFile" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< simulationFile_type > r (
        simulationFile_traits::create (i, f, this));

      if (!simulationFile_.present ())
      {
        this->simulationFile_.set (r);
        continue;
      }
    }

    // saveFile
    //
    if (n.name () == "saveFile" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< saveFile_type > r (
        saveFile_traits::create (i, f, this));

      if (!this->saveFile_)
      {
        this->saveFile_.set (r);
        continue;
      }
    }

    break;
  }

  if (!delta_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "delta",
      "");
  }

  if (!end_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "end",
      "");
  }

  if (!output_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "output",
      "");
  }

  if (!simulationFile_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "simulationFile",
      "");
  }
}

config_t* config_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class config_t (*this, f, c);
}

config_t::
~config_t ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::config_t >
configSim (const ::std::string& u,
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

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (const ::std::string& u,
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

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (const ::std::string& u,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::configSim (isrc, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::configSim (isrc, h, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::configSim (isrc, h, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           const ::std::string& sid,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::configSim (isrc, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           const ::std::string& sid,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::configSim (isrc, h, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::std::istream& is,
           const ::std::string& sid,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::configSim (isrc, h, f, p);
}

::std::auto_ptr< ::config_t >
configSim (::xercesc::InputSource& i,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (::xercesc::InputSource& i,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (::xercesc::InputSource& i,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::config_t > r (
    ::configSim (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::config_t >
configSim (const ::xercesc::DOMDocument& d,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::config_t > r (
      ::configSim (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "configSim" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::config_t > r (
      ::xsd::cxx::tree::traits< ::config_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "configSim",
    "");
}

::std::auto_ptr< ::config_t >
configSim (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
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

  if (n.name () == "configSim" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::config_t > r (
      ::xsd::cxx::tree::traits< ::config_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "configSim",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

