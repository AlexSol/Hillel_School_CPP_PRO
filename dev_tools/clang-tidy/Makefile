CLANG_TIDY := clang-tidy
SOURCE := example.cpp
COMMON_ARGS := --config-file=.clang-tidy --
COMPILE_ARGS := -std=c++20 -I.

.PHONY: show check fix reset help

help:
	@printf '%s\n' 'make show  - print clang-tidy diagnostics' 'make check - fail if clang-tidy finds diagnostics' 'make fix   - apply automatic clang-tidy fixes' 'make reset - restore intentionally problematic demo file'

show:
	$(CLANG_TIDY) $(SOURCE) $(COMMON_ARGS) $(COMPILE_ARGS)

check:
	$(CLANG_TIDY) $(SOURCE) --warnings-as-errors='*' $(COMMON_ARGS) $(COMPILE_ARGS)

fix:
	$(CLANG_TIDY) $(SOURCE) --fix --format-style=file $(COMMON_ARGS) $(COMPILE_ARGS)

reset:
	printf '%s\n' '#include <iostream>' '#include <vector>' '' 'typedef std::vector<int>::iterator IntIterator;' '' 'int main()' '{' '    int* ptr = NULL;' '' '    if (ptr == NULL)' '    {' '        std::cout << "ptr is null" << std::endl;' '    }' '' '    std::vector<int> values = {1, 2, 3};' '    IntIterator it = values.begin();' '' '    std::cout << *it << std::endl;' '    return 0;' '}' > $(SOURCE)