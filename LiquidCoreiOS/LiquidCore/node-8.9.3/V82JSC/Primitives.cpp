/*
 * Copyright (c) 2018 Eric Lange
 *
 * Distributed under the MIT License.  See LICENSE.md at
 * https://github.com/LiquidPlayer/LiquidCore for terms and conditions.
 */
#include "V82JSC.h"

using namespace v8;

double Number::Value() const
{
    Local<Context> context = V82JSC::ToCurrentContext(this);
    JSContextRef ctx = V82JSC::ToContextRef(context);
    JSValueRef value = V82JSC::ToJSValueRef(this, context);

    return JSValueToNumber(ctx, value, 0);
}

Local<Number> Number::New(Isolate* isolate, double value)
{
    EscapableHandleScope scope(isolate);
    JSContextRef ctx;
    ContextImpl* ci;
    Local<Context> context = V82JSC::OperatingContext(isolate);
    ctx = V82JSC::ToContextRef(context);
    ci = V82JSC::ToContextImpl(context);
    return scope.Escape(ValueImpl::New(ci, JSValueMakeNumber(ctx, value)).As<Number>());
}

Local<Integer> Integer::New(Isolate* isolate, int32_t value)
{
    return Number::New(isolate, value).As<Integer>();
}
Local<Integer> Integer::NewFromUnsigned(Isolate* isolate, uint32_t value)
{
    return Number::New(isolate, value).As<Integer>();
}
int64_t Integer::Value() const
{
    return reinterpret_cast<const Number*>(this)->Value();
}

int32_t Int32::Value() const
{
    return reinterpret_cast<const Number*>(this)->Value();
}

uint32_t Uint32::Value() const
{
    return reinterpret_cast<const Number*>(this)->Value();
}

bool v8::Boolean::Value() const
{
    Local<Context> context = V82JSC::ToCurrentContext(this);
    JSContextRef ctx = V82JSC::ToContextRef(context);
    JSValueRef value = V82JSC::ToJSValueRef(this, context);

    return JSValueToBoolean(ctx, value);
}

/**
 * Returns the identity hash for this object. The current implementation
 * uses an inline property on the object to store the identity hash.
 *
 * The return value will never be 0. Also, it is not guaranteed to be
 * unique.
 */
int Name::GetIdentityHash()
{
    return 1;
}

