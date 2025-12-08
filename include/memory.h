/*
* MIT License
*
* Copyright (c) 2025 Laurin "lyniat" Muth
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
*         of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
*         to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*         copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
*         copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once
#include <cstdlib>

typedef void *(*ossp_malloc_fn)(size_t size);
typedef void *(*ossp_calloc_fn)(size_t num, size_t size);
typedef void *(*ossp_realloc_fn)(void* ptr, size_t size);
typedef void  (*ossp_free_fn)(void* ptr);

typedef struct ossp_allocator {
    ossp_malloc_fn  malloc_fn = malloc;
    ossp_calloc_fn  calloc_fn = calloc;
    ossp_realloc_fn realloc_fn = realloc;
    ossp_free_fn    free_fn = free;
} ossp_allocator;

inline ossp_allocator ossp_def_allocator;
inline ossp_allocator* ossp_extern_allocator = &ossp_def_allocator;

static void* ossp_malloc(size_t size) {
    return ossp_extern_allocator->malloc_fn(size);
}

static void* ossp_calloc(size_t num, size_t size) {
    return ossp_extern_allocator->calloc_fn(num, size);
}

static void* ossp_realloc(void* ptr, size_t size) {
    return ossp_extern_allocator->realloc_fn(ptr, size);
}

static void ossp_free(void* ptr) {
    return ossp_extern_allocator->free_fn(ptr);
}

static void set_extern_allocator(const ossp_allocator &allocator) {
    ossp_extern_allocator->malloc_fn = allocator.malloc_fn;
    ossp_extern_allocator->calloc_fn = allocator.calloc_fn;
    ossp_extern_allocator->realloc_fn = allocator.realloc_fn;
    ossp_extern_allocator->free_fn = allocator.free_fn;
}
