#pragma once


template<typename T>
struct inheritor : T {};

struct test : inheritor<test> {};