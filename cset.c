#define COBJECT_IMPLEMENTATION
 
#ifndef CSet_Params
#error "CSet Params is not defined"
#endif

#define CSet_T TEMPLATE(CSet, CSet_Params)
#define CSet_Class_T TEMPLATE(CSet, CSet_Params, Class)
#define T1 T_Param(1, CSet_Params)
#define CSet_Method(method) TEMPLATE(CSet, CSet_Params, method)

static void CSet_Method(delete)(struct Object * const obj);
static uint32_t CSet_Method(size)(union CSet_T * const);
static void CSet_Method(clear)(union CSet_T * const);
static T1 * CSet_Method(begin)(union CSet_T * const);
static T1 * CSet_Method(end)(union CSet_T * const);
static T1 * CSet_Method(at)(union CSet_T * const, uint32_t const);
static T1 CSet_Method(access)(union CSet_T * const, uint32_t const);
static void CSet_Method(insert)(union CSet_T * const, T1 const);
static T1 * CSet_Method(find)(union CSet_T * const, T1 const);
static void CSet_Method(erase)(union CSet_T * const, T1 const);
static int CSet_Method(compare)(void const *, void const *);

union CSet_Class_T CSet_Class_T =
{
	{{CSet_Method(delete), NULL},
    CSet_Method(size),
    CSet_Method(clear),
    CSet_Method(begin),
    CSet_Method(end),
    CSet_Method(at),
    CSet_Method(access),
    CSet_Method(insert),
    CSet_Method(find),
    CSet_Method(erase),
    CSet_Method(compare)
	}
};

static union CSet_T CSet_T = {NULL};

void CSet_Method(delete)(struct Object * const obj)
{
	union CSet_T * const this = (union CSet_T *) Object_Cast(&CSet_Class_T.Class, obj);
	Isnt_Nullptr(this, );
	this->vtbl->clear(this);
}

int CSet_Method(compare)(void const * a, void const * b)
{
	return memcmp(a,b, sizeof(T1));
}
 
void Method_Name(Populate, CSet, CSet_Params)(union CSet_T * const this, T1 * const buff, size_t const buff_size)
{
	if(NULL == CSet_T.vtbl)
	{
		CSet_T.vtbl = &CSet_Class_T;
		CSet_T.i = 0;
		CSet_T.buffer = NULL;
	}
	
	memcpy(this, &CSet_T, sizeof(CSet_T));
	
    this->capacity = buff_size;
    this->buffer = buff;
}

T1 * CSet_Method(begin)(union CSet_T * const this)
{
    return this->buffer;
}

T1 * CSet_Method(end)(union CSet_T * const this)
{
    return this->buffer + this->vtbl->size(this);
}

uint32_t CSet_Method(size)(union CSet_T * const this)
{
    return this->i;
}

void CSet_Method(clear)(union CSet_T * const this)
{
	while(this->i)
	{
		T1 * const it = this->vtbl->begin(this);
		this->vtbl->erase(this, *it);
	}
}

void CSet_Method(insert)(union CSet_T * const this, T1 const value)
{
    if (this->i >= this->capacity) return;

	T1 * end = this->vtbl->end(this);
	T1 * found = this->vtbl->find(this, value);

	if(end != found) return;

    this->buffer[this->i++] = value;
    qsort(this->buffer, this->i, sizeof(T1), this->vtbl->compare);
}

void CSet_Method(erase)(union CSet_T * const this,
      T1 const value)
{
    if (this->i >= this->capacity) return;

	T1 * end = this->vtbl->end(this);
	T1 * found = this->vtbl->find(this, value);

	if(end == found) return;

#ifdef CSET_DELETABLE
	_delete(found);
#endif

	memset(found, 0, sizeof(found[0]));
    memcpy(found - 1, found, (size_t) end - (size_t)found);
}

T1 * CSet_Method(find)(union CSet_T * const this, T1 const key)
{
   T1 * const found = bsearch(&key, this->buffer, this->i, sizeof(T1), this->vtbl->compare);
   return (found)? found : this->vtbl->end(this);
}

T1 * CSet_Method(at)(union CSet_T * const this, uint32_t const index)
{
    return this->buffer + index;
}

T1 CSet_Method(access)(union CSet_T * const this, uint32_t const index)
{
    return this->buffer[index];
}