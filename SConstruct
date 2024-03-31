# type: ignore

# gnu arm toolchain must be already in system path
 
import os
env = Environment(ENV = os.environ)
 
env['AR'] = 'arm-none-eabi-ar'
env['AS'] = 'arm-none-eabi-as'
env['CC'] = 'arm-none-eabi-gcc'
env['CXX'] = 'arm-none-eabi-g++'
env['LINK'] = 'arm-none-eabi-g++'                # predefined is 'arm-none-eabi-gcc'
env['RANLIB'] = 'arm-none-eabi-ranlib'
env['OBJCOPY'] = 'arm-none-eabi-objcopy'
env['PROGSUFFIX'] = '.elf'
# env['LINKCOMSTR'] = "Linking $TARGET from $SOURCES"

# include locations
env['CPPPATH'] = [
    './',
    ]
 
# compiler flags
env.Append(CCFLAGS = [
    "-I./rtos",
    "-I.",
    "-Os",
    "-std=c99",
    "-ggdb3",
    "-mcpu=cortex-m4",
    "-mthumb",
    "-mfloat-abi=hard",
    "-mfpu=fpv4-sp-d16",
    "-Wextra",
    "-Wshadow",
    "-Wimplicit-function-declaration",
    "-Wredundant-decls",
    "-Wmissing-prototypes",
    "-Wstrict-prototypes",
    "-fno-common",
    "-ffunction-sections",
    "-fdata-sections",
    "-MD",
    "-Wall",
    "-Wundef",
    "-DSTM32F4",
    "-DSTM32F401RE",
    "-I.//libopencm3//include",
])
 
# linker flags
env.Append(LINKFLAGS = [
#   "--static",
    "-nostartfiles",
    "-Tgenerated.stm32f401re.ld",  # Use the generated linker script
    "-mcpu=cortex-m4",
    "-mthumb",
    "-mfloat-abi=hard",
    "-mfpu=fpv4-sp-d16",
    "-ggdb3",
    "-Wl,-Map=main.map",
    "-Wl,--cref",
    "-Wl,--gc-sections",
    "-L", ".//libopencm3//lib",  # Library path
]) 

# these flags must be at the end of the linker command
env.Append(_LIBFLAGS = [
    "-lopencm3_stm32f4",  # Link with opencm3 library
    "-Wl,--start-group",
    "-lc",  # Link with standard C library
    "-lgcc",
    "-lnosys",
    "-Wl,--end-group"
])
 
# defines
env.Append(CPPDEFINES = [
    'STM32F401xx',
])
 
# Define source files
obj_files = Glob('*.c') + [
    'rtos/heap_4.c',
    'rtos/list.c',
    'rtos/port.c',
    'rtos/queue.c',
    'rtos/tasks.c',
    'rtos/opencm3_shim'
]

# obj_files = Glob('*.c') + Glob('rtos/*.c') 

# Compile the source files into object files
obj_files = [env.Object(source=file) for file in obj_files]

elf_target = 'main.elf'
bin_target = 'main.bin'
map_target = 'main.map'

env.Clean('.', [elf_target, bin_target, map_target])

# build everything
prg = env.Program(
    target = 'main',
    source = obj_files
)
 
# binary file builder
def arm_generator(source, target, env, for_signature):
    return '$OBJCOPY -O binary %s %s'%(source[0], target[0])

env.Append(BUILDERS = {
    'Objcopy': Builder(
        generator=arm_generator,
        suffix='.bin',
        src_suffix='.elf'
    )
})
 
bin_target = env.Objcopy(prg)

env.Depends(bin_target, prg)