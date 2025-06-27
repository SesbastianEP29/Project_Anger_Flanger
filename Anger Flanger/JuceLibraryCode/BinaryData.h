/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Fondondo_jpg;
    const int            Fondondo_jpgSize = 147755;

    extern const char*   knob101st111si_png;
    const int            knob101st111si_pngSize = 61222;

    extern const char*   miknob_png;
    const int            miknob_pngSize = 1560861;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 3;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
