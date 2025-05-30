#include "std_include.hpp"
#include "cpu_context.hpp"

namespace cpu_context
{
    void restore(x86_64_emulator& emu, const CONTEXT64& context)
    {
        if ((context.ContextFlags & CONTEXT_DEBUG_REGISTERS_64) == CONTEXT_DEBUG_REGISTERS_64)
        {
            emu.reg(x86_register::dr0, context.Dr0);
            emu.reg(x86_register::dr1, context.Dr1);
            emu.reg(x86_register::dr2, context.Dr2);
            emu.reg(x86_register::dr3, context.Dr3);
            emu.reg(x86_register::dr6, context.Dr6);
            emu.reg(x86_register::dr7, context.Dr7);
        }

        if ((context.ContextFlags & CONTEXT_CONTROL_64) == CONTEXT_CONTROL_64)
        {
            emu.reg<uint16_t>(x86_register::ss, context.SegSs);
            emu.reg<uint16_t>(x86_register::cs, context.SegCs);

            emu.reg(x86_register::rip, context.Rip);
            emu.reg(x86_register::rsp, context.Rsp);

            emu.reg<uint32_t>(x86_register::eflags, context.EFlags);
        }

        if ((context.ContextFlags & CONTEXT_INTEGER_64) == CONTEXT_INTEGER_64)
        {
            emu.reg(x86_register::rax, context.Rax);
            emu.reg(x86_register::rbx, context.Rbx);
            emu.reg(x86_register::rcx, context.Rcx);
            emu.reg(x86_register::rdx, context.Rdx);
            emu.reg(x86_register::rbp, context.Rbp);
            emu.reg(x86_register::rsi, context.Rsi);
            emu.reg(x86_register::rdi, context.Rdi);
            emu.reg(x86_register::r8, context.R8);
            emu.reg(x86_register::r9, context.R9);
            emu.reg(x86_register::r10, context.R10);
            emu.reg(x86_register::r11, context.R11);
            emu.reg(x86_register::r12, context.R12);
            emu.reg(x86_register::r13, context.R13);
            emu.reg(x86_register::r14, context.R14);
            emu.reg(x86_register::r15, context.R15);
        }

        /*if ((context.ContextFlags & CONTEXT_SEGMENTS) == CONTEXT_SEGMENTS)
        {
            emu.reg<uint16_t>(x86_register::ds, context.SegDs);
            emu.reg<uint16_t>(x86_register::es, context.SegEs);
            emu.reg<uint16_t>(x86_register::fs, context.SegFs);
            emu.reg<uint16_t>(x86_register::gs, context.SegGs);
        }*/

        if ((context.ContextFlags & CONTEXT_FLOATING_POINT_64) == CONTEXT_FLOATING_POINT_64)
        {
            emu.reg<uint16_t>(x86_register::fpcw, context.FltSave.ControlWord);
            emu.reg<uint16_t>(x86_register::fpsw, context.FltSave.StatusWord);
            emu.reg<uint16_t>(x86_register::fptag, context.FltSave.TagWord);

            for (int i = 0; i < 8; i++)
            {
                const auto reg = static_cast<x86_register>(static_cast<int>(x86_register::st0) + i);
                emu.reg<M128A>(reg, context.FltSave.FloatRegisters[i]);
            }
        }

        if ((context.ContextFlags & CONTEXT_XSTATE_64) == CONTEXT_XSTATE_64)
        {
            emu.reg<uint32_t>(x86_register::mxcsr, context.MxCsr);

            for (int i = 0; i < 16; i++)
            {
                const auto reg = static_cast<x86_register>(static_cast<int>(x86_register::xmm0) + i);
                emu.reg<M128A>(reg, (&context.Xmm0)[i]);
            }
        }
    }

    void save(x86_64_emulator& emu, CONTEXT64& context)
    {
        if ((context.ContextFlags & CONTEXT_DEBUG_REGISTERS_64) == CONTEXT_DEBUG_REGISTERS_64)
        {
            context.Dr0 = emu.reg(x86_register::dr0);
            context.Dr1 = emu.reg(x86_register::dr1);
            context.Dr2 = emu.reg(x86_register::dr2);
            context.Dr3 = emu.reg(x86_register::dr3);
            context.Dr6 = emu.reg(x86_register::dr6);
            context.Dr7 = emu.reg(x86_register::dr7);
        }

        if ((context.ContextFlags & CONTEXT_CONTROL_64) == CONTEXT_CONTROL_64)
        {
            context.SegSs = emu.reg<uint16_t>(x86_register::ss);
            context.SegCs = emu.reg<uint16_t>(x86_register::cs);
            context.Rip = emu.reg(x86_register::rip);
            context.Rsp = emu.reg(x86_register::rsp);
            context.EFlags = emu.reg<uint32_t>(x86_register::eflags);
        }

        if ((context.ContextFlags & CONTEXT_INTEGER_64) == CONTEXT_INTEGER_64)
        {
            context.Rax = emu.reg(x86_register::rax);
            context.Rbx = emu.reg(x86_register::rbx);
            context.Rcx = emu.reg(x86_register::rcx);
            context.Rdx = emu.reg(x86_register::rdx);
            context.Rbp = emu.reg(x86_register::rbp);
            context.Rsi = emu.reg(x86_register::rsi);
            context.Rdi = emu.reg(x86_register::rdi);
            context.R8 = emu.reg(x86_register::r8);
            context.R9 = emu.reg(x86_register::r9);
            context.R10 = emu.reg(x86_register::r10);
            context.R11 = emu.reg(x86_register::r11);
            context.R12 = emu.reg(x86_register::r12);
            context.R13 = emu.reg(x86_register::r13);
            context.R14 = emu.reg(x86_register::r14);
            context.R15 = emu.reg(x86_register::r15);
        }

        if ((context.ContextFlags & CONTEXT_SEGMENTS_64) == CONTEXT_SEGMENTS_64)
        {
            context.SegDs = emu.reg<uint16_t>(x86_register::ds);
            context.SegEs = emu.reg<uint16_t>(x86_register::es);
            context.SegFs = emu.reg<uint16_t>(x86_register::fs);
            context.SegGs = emu.reg<uint16_t>(x86_register::gs);
        }

        if ((context.ContextFlags & CONTEXT_FLOATING_POINT_64) == CONTEXT_FLOATING_POINT_64)
        {
            context.FltSave.ControlWord = emu.reg<uint16_t>(x86_register::fpcw);
            context.FltSave.StatusWord = emu.reg<uint16_t>(x86_register::fpsw);
            context.FltSave.TagWord = static_cast<BYTE>(emu.reg<uint16_t>(x86_register::fptag));
            for (int i = 0; i < 8; i++)
            {
                const auto reg = static_cast<x86_register>(static_cast<int>(x86_register::st0) + i);
                context.FltSave.FloatRegisters[i] = emu.reg<M128A>(reg);
            }
        }

        if ((context.ContextFlags & CONTEXT_INTEGER_64) == CONTEXT_INTEGER_64)
        {
            context.MxCsr = emu.reg<uint32_t>(x86_register::mxcsr);
            for (int i = 0; i < 16; i++)
            {
                const auto reg = static_cast<x86_register>(static_cast<int>(x86_register::xmm0) + i);
                (&context.Xmm0)[i] = emu.reg<M128A>(reg);
            }
        }
    }
}
