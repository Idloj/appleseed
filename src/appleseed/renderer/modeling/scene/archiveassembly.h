
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2016-2017 Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_MODELING_SCENE_ARCHIVEASSEMBLY_H
#define APPLESEED_RENDERER_MODELING_SCENE_ARCHIVEASSEMBLY_H

// appleseed.renderer headers.
#include "renderer/modeling/scene/basegroup.h"
#include "renderer/modeling/scene/iassemblyfactory.h"
#include "renderer/modeling/scene/proceduralassembly.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"
#include "foundation/utility/autoreleaseptr.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Forward declarations.
namespace foundation    { class IAbortSwitch; }
namespace foundation    { class StringArray; }
namespace foundation    { class StringDictionary; }
namespace renderer      { class ParamArray; }
namespace renderer      { class Project; }

namespace renderer
{

//
// An archive assembly loads and references geometries, materials and lights
// from other appleseed projects.
//

class APPLESEED_DLLSYMBOL ArchiveAssembly
  : public ProceduralAssembly
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying the model of this entity.
    const char* get_model() const override;

    // Expose asset file paths referenced by this entity to the outside.
    void collect_asset_paths(foundation::StringArray& paths) const override;
    void update_asset_paths(const foundation::StringDictionary& mappings) override;

    bool expand_contents(
        const Project&              project,
        const Assembly*             parent,
        foundation::IAbortSwitch*   abort_switch = nullptr) override;

  private:
    friend class ArchiveAssemblyFactory;

    // Constructor.
    ArchiveAssembly(
        const char*                 name,
        const ParamArray&           params);

    bool m_archive_opened;
};


//
// ArchiveAssembly factory.
//

class APPLESEED_DLLSYMBOL ArchiveAssemblyFactory
  : public IAssemblyFactory
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying this assembly model.
    const char* get_model() const override;

    // Create a new assembly.
    foundation::auto_release_ptr<Assembly> create(
        const char*         name,
        const ParamArray&   params = ParamArray()) const override;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_SCENE_ARCHIVEASSEMBLY_H
