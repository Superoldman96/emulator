#include "emulation_test_utils.hpp"

namespace test
{
    TEST(EmulationTest, BasicEmulationWorks)
    {
        auto emu = create_sample_emulator();
        emu.start();

        ASSERT_TERMINATED_SUCCESSFULLY(emu);
    }

    TEST(EmulationTest, CountedEmulationWorks)
    {
        constexpr auto count = 200000;

        auto emu = create_sample_emulator();
        emu.start(count);

        ASSERT_EQ(emu.get_executed_instructions(), count);
    }

    TEST(EmulationTest, CountedEmulationIsAccurate)
    {
        auto emu = create_sample_emulator();
        emu.start();

        ASSERT_TERMINATED_SUCCESSFULLY(emu);

        const auto executedInstructions = emu.get_executed_instructions();

        auto new_emu = create_sample_emulator();

        constexpr auto offset = 1;
        const auto instructionsToExecute = executedInstructions - offset;

        new_emu.start(static_cast<size_t>(instructionsToExecute));

        ASSERT_EQ(new_emu.get_executed_instructions(), instructionsToExecute);
        ASSERT_NOT_TERMINATED(new_emu);

        new_emu.start(offset);

        ASSERT_TERMINATED_SUCCESSFULLY(new_emu);
        ASSERT_EQ(new_emu.get_executed_instructions(), executedInstructions);
    }
}
