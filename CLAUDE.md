# CLAUDE.md — XFSTL Codebase Guide

## Project Overview

XFSTL is an educational, from-scratch C++ implementation of the Standard Template Library (STL). The project's goal is deep learning of template metaprogramming, iterator design patterns, and data structure internals. All implementations live in the custom `xf` namespace.

**Language:** C++98/03
**Build System:** Visual Studio MSBuild (MSVC)
**Platform Target:** Win32 (x86) / Windows
**No external dependencies** — only standard C++ headers are used.

---

## Repository Structure

```
XFSTL/
├── CLAUDE.md                        # This file
├── README.md                        # Brief project description
├── .gitignore                       # Visual Studio ignore patterns
├── design notes.txt                 # Design decisions (Chinese)
├── questions.txt                    # Implementation questions (Chinese)
├── Exception.jpg                    # Exception-related image
├── STL Design Diagram.vsd           # Visio design diagram
└── STL/
    └── STL/                         # All source code lives here
        ├── *.hpp                    # Container & iterator implementations
        ├── *.cpp                    # Test files + main entry point
        ├── STL.vcxproj              # Visual Studio project file
        └── STL.sln                  # Visual Studio solution file
```

---

## Source File Map

### Containers (`STL/STL/*.hpp`)

| File | Purpose |
|------|---------|
| `vector.hpp` | Dynamic array — 808 lines, full implementation |
| `list.hpp` | Doubly-linked list — 731 lines |
| `deque.hpp` | Double-ended queue with segment-based storage — 1265 lines |
| `string.hpp` | Basic string wrapper around `vector` (incomplete/stub) |
| `stack.hpp` | LIFO stack adapter — 76 lines |
| `queue.hpp` | FIFO queue adapter — 74 lines |
| `priority_queue.hpp` | Priority queue with heap operations — 165 lines |

### Iterators (`STL/STL/*.hpp`)

| File | Purpose |
|------|---------|
| `_Iterator_Traits.hpp` | Iterator traits and category tag types |
| `_Vector_iterator.hpp` | Mutable random-access iterator for `vector` |
| `_Vector_const_iterator.hpp` | Const random-access iterator for `vector` |
| `_List_Iterator.hpp` | Mutable bidirectional iterator for `list` |
| `_List_Const_Iterator.hpp` | Const bidirectional iterator for `list` |
| `_Deque_Iterator.hpp` | Mutable random-access iterator for `deque` |
| `_Deque_Const_Iterator.hpp` | Const random-access iterator for `deque` |
| `_Reverse_Iterator.hpp` | Generic reverse iterator adapter |

### Algorithms & Utilities (`STL/STL/*.hpp`)

| File | Purpose |
|------|---------|
| `common_algorithm.hpp` | `swap`, `min`, `max`, `sgn` |
| `memory.hpp` | `uninitialized_copy`, `uninitialized_fill` |
| `sort.hpp` | Public sort interface (delegates to quicksort) |
| `quick_sort.hpp` | Quicksort implementation |
| `heap_sort.hpp` | Heapsort implementation |
| `list_item.hpp` | Node struct for linked list |

### Tests (`STL/STL/*.cpp`)

| File | Purpose |
|------|---------|
| `main.cpp` | Entry point; calls all test functions |
| `vector_test.cpp` | Vector tests — 1141 lines |
| `list_test.cpp` | List tests — 560 lines |
| `deque_test.cpp` | Deque tests — 513 lines |
| `adapter_test.cpp` | Stack/queue adapter tests |
| `sort_test.cpp` | Sorting algorithm tests — 165 lines |
| `priority_queue_test.cpp` | Priority queue tests — 109 lines |
| `string_test.cpp` | String tests (minimal) |
| `multifile_test.cpp` | Cross-file compilation tests |
| `test.hpp` | Test utilities and helper classes |

---

## Build & Run

### Prerequisites
- Visual Studio (2010 or later) on Windows
- MSVC compiler (no GCC/Clang support assumed)

### Building
Open `STL/STL.sln` in Visual Studio and build with **Debug** or **Release** configuration (Win32).

There is no Makefile or CMake — the only build system is MSBuild via the `.vcxproj` file.

### Running Tests
Build the project and run the resulting executable. `main.cpp` calls all test functions sequentially:

```cpp
vector_test();
list_test();
deque_test();
adapter_test();
sort_test();
string_test();
multi_file_test();
```

Tests use `assert()` from `<cassert>` — a failing assert aborts the process immediately with an error message.

There is no test runner, no CI/CD pipeline, and no external test framework.

---

## Code Conventions

### Naming
| Element | Convention | Example |
|---------|-----------|---------|
| Classes | PascalCase (often with leading `_`) | `_Vector_Iterator`, `priority_queue` |
| Private data members | Trailing underscore | `size_`, `capacity_`, `p_`, `heap_` |
| Template parameters | Leading underscore | `_Iter`, `_First`, `_Last`, `_Container` |
| Internal helpers | Leading underscore | `_distance`, `_sort`, `_get_iter_category_var` |
| Namespace | `xf` | `xf::vector<int>` |

### File Organization
- All container/iterator implementations are **header-only** (`.hpp` files contain full definitions).
- Test logic lives in `.cpp` files; one `.cpp` per container/algorithm under test.
- `main.cpp` is the sole entry point and only calls test functions.

### C++ Style
- **Standard:** C++98/03 — no C++11 features (no `auto`, no range-for, no lambdas, no `nullptr`).
- **Exception specs:** Old-style `throw(std::out_of_range)` used.
- **Memory:** Raw allocation via `operator new` / `operator new[]` + placement new for construction.
- **MSVC pragmas:** `#pragma warning(disable:4290, 4996)` suppress specific MSVC warnings.
- **Comments:** Mix of English and Chinese throughout the codebase.

### Design Patterns in Use

1. **Iterator Inheritance:** Non-const iterators inherit from their const counterparts to avoid code duplication.
2. **Reverse Iterator Adapter:** `_Reverse_Iterator<T>` is a generic wrapper around any iterator type.
3. **Iterator Traits & Tag Dispatch:** `_Iterator_Traits.hpp` defines category tags used for algorithm dispatch.
4. **Template Specialization Workarounds:** Explicit specializations for `int` parameters work around MSVC template resolution quirks.
5. **Segment-Based Deque:** `deque` uses a map of fixed-size segments (not a contiguous buffer) — see `deque.hpp` and `design notes.txt` for rationale.

---

## Key Design Decisions

Detailed design rationale is in `design notes.txt` (written in Chinese). Highlights:

- **Iterator hierarchy:** Const iterators are base classes; mutable iterators extend them. This ensures a non-const iterator can be passed where a const iterator is expected.
- **Reverse iterator:** Wraps a forward iterator; `operator*` dereferences the position one before the stored iterator (mirrors standard behavior).
- **Deque internals:** Uses a central `map_` array of pointers to fixed-size `_block`s. Iterators carry a pointer to their block, the map, and the map capacity to support O(1) random access.
- **Sorting:** `sort.hpp` provides a thin dispatch layer; the default algorithm is quicksort. Heapsort is also available.

---

## What Is (and Is Not) Implemented

### Implemented
- `xf::vector<T>` — nearly complete (construction, iterators, insert, erase, push_back, etc.)
- `xf::list<T>` — doubly-linked list with bidirectional iterators
- `xf::deque<T>` — segment-based deque with random-access iterators
- `xf::stack<T>`, `xf::queue<T>` — adapters over deque/list
- `xf::priority_queue<T>` — min/max heap
- `xf::sort()` — quicksort and heapsort
- Reverse iterators for all containers
- Iterator traits and category dispatch

### Not Implemented / Incomplete
- `xf::string` — stub only, wraps `vector<char>` with no extra methods
- Associative containers (`map`, `set`, `unordered_map`, etc.)
- Algorithms beyond sorting (`find`, `copy`, `transform`, etc.)
- Allocator support
- Move semantics (project targets C++98)

---

## Working with This Codebase

### Adding a New Container
1. Create `STL/STL/<name>.hpp` with the implementation in the `xf` namespace.
2. Create matching iterator files `_<Name>_Iterator.hpp` and `_<Name>_Const_Iterator.hpp` if needed.
3. Create `STL/STL/<name>_test.cpp` with thorough `assert`-based tests.
4. Add a `<name>_test()` call in `main.cpp`.
5. Add all new files to `STL.vcxproj`.

### Adding a New Algorithm
1. Add the function template to an appropriate `.hpp` (new file or `common_algorithm.hpp`).
2. Add tests in `sort_test.cpp` or a new `<algo>_test.cpp`.

### Modifying Existing Containers
- Read the relevant `.hpp` carefully — the template logic is non-trivial.
- Check `design notes.txt` for design rationale before changing iterator inheritance or deque internals.
- Keep all changes within the `xf` namespace.
- Run the full test suite after any change by building and executing the binary.

### Things to Avoid
- Do **not** use C++11 or later features — the project targets C++98.
- Do **not** introduce external libraries or dependencies.
- Do **not** rename private members without the trailing underscore — this is a firm convention.
- Do **not** flatten iterator hierarchy (const/non-const inheritance is intentional).

---

## Git Workflow

- **Main branch:** `master`
- **Feature branches:** `claude/<description>-<id>` pattern used for AI-assisted development
- **No CI/CD** — all testing is manual (build in Visual Studio, run the binary)

---

## Documentation Files

| File | Language | Content |
|------|----------|---------|
| `README.md` | English | One-line project summary |
| `design notes.txt` | Chinese | Iterator design, deque internals, const-correctness rationale |
| `questions.txt` | Chinese | Open implementation questions |
| `STL Design Diagram.vsd` | Visual | Class/architecture diagram (Visio format) |
