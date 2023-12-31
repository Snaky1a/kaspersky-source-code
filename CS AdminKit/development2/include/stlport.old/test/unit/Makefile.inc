# -*- makefile -*- Time-stamp: <04/03/12 07:57:22 ptr>
# $Id: Makefile.inc,v 1.2.2.7 2004/10/31 14:43:09 dums Exp $

# this is the version number of needed STLport library for linking
LIBMAJOR = 5
LIBMINOR = 0

PRGNAME = stl_unit_test
SRC_CPP = cppunit/test_main.cpp \
	accum_test.cpp \
	adj_test.cpp \
	advance_test.cpp \
	alg_test.cpp \
	allocator_test.cpp \
	bcompos_test.cpp \
	bind_test.cpp \
	binsert_test.cpp \
	bitset_test.cpp \
	bnegate_test.cpp \
	bound_test.cpp \
	bsearch_test.cpp \
	bvector_test.cpp \
	copy_test.cpp \
	count_test.cpp \
	deque_test.cpp \
	divides_test.cpp \
	equal_test.cpp \
	exception_test.cpp \
	fill_test.cpp \
	find_test.cpp \
	finsert_test.cpp \
	floatio_test.cpp \
	foreach_test.cpp \
	func_test.cpp \
	generator_test.cpp \
	greater_test.cpp \
	hash_test.cpp \
	heap_test.cpp \
	includes_test.cpp \
	innerprod_test.cpp \
	inplace_test.cpp \
	insert_test.cpp \
	ioiter_test.cpp \
	iota_test.cpp \
	istmit_test.cpp \
	iter_test.cpp \
	less_test.cpp \
	lexcmp_test.cpp \
	list_test.cpp \
	limits_test.cpp \
	logic_test.cpp \
	map_test.cpp \
	max_test.cpp \
	merge_test.cpp \
	mfunptr_test.cpp \
	min_test.cpp \
	mismatch_test.cpp \
	modulus_test.cpp \
	multiset_test.cpp \
	mvctor_test.cpp \
	neq_test.cpp \
	nthelm_test.cpp \
	ostmit_test.cpp \
	pair_test.cpp \
	partial_test.cpp \
	partition_test.cpp \
	perm_test.cpp \
	plusminus_test.cpp \
	ptr2_test.cpp \
	ptrspec_test.cpp \
	queue_test.cpp \
	rawriter_test.cpp \
	reviter_test.cpp \
	rm_cp_test.cpp \
	rndshf_test.cpp \
	rope_test.cpp \
	rotate_test.cpp \
	search_test.cpp \
	set_test.cpp \
	setdiff_test.cpp \
	setinter_test.cpp \
	setunion_test.cpp \
	slist_test.cpp \
	sort_test.cpp \
	stack_test.cpp \
	string_test.cpp \
	swap_test.cpp \
	times_test.cpp \
	transform_test.cpp \
	type_traits_test.cpp \
	unary_test.cpp \
	unique_test.cpp \
	vector_test.cpp \
	sstream_test.cpp \
	fstream_test.cpp \
	locale_test.cpp
