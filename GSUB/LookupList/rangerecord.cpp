#include "rangerecord.h"

RangeRecord::RangeRecord(FontSeeker& fs)
{
    start_glyph_id = fs.read16();
    end_glyph_id = fs.read16();
    start_coverage_index = fs.read16();
}
