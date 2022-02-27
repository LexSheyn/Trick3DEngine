#pragma once

// Custom defines:
#if _DEBUG
// In Debug mode does nothing.
#define T3D_INLINE
#else
// In Release mode inlines the function call.
#define T3D_INLINE inline
#endif