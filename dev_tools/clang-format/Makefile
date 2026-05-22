CLANG_FORMAT := clang-format
SOURCE := example.cpp

.PHONY: show format check reset help

help:
	@printf '%s\n' 'make show   - preview formatted output' 'make format - apply formatting to example.cpp' 'make check  - fail if example.cpp is not formatted' 'make reset  - restore intentionally unformatted demo file'

show:
	$(CLANG_FORMAT) -style=file $(SOURCE)

format:
	$(CLANG_FORMAT) -i -style=file $(SOURCE)

check:
	@tmp_file=$$(mktemp); \
	$(CLANG_FORMAT) -style=file $(SOURCE) > $$tmp_file; \
	diff -u $(SOURCE) $$tmp_file; \
	status=$$?; \
	rm -f $$tmp_file; \
	exit $$status

reset:
	printf '%s\n' '#include <iostream>' '#include <vector>' '' 'int   sum( const std::vector<int>& values ){' 'int result=0;' 'for(auto value:values){result+=value;}' 'return result;' '}' '' 'int main(){std::vector<int> values={1,2,3,4,5};if(sum(values)>10){std::cout<<"sum is greater than 10"<<std::endl;}else{std::cout<<"sum is 10 or less"<<std::endl;}return 0;}' > $(SOURCE)