project('embedded_project', 'c',
  version : '1.0',
  meson_version : '>=0.58',
  default_options : ['buildtype=debugoptimized'])

# Tools from cross file
objcopy = find_program('objcopy')
size = find_program('size')

# Copy linker script to build directory
linker_script = configure_file(
  input: 'generated.stm32f401re.ld',
  output: 'generated.stm32f401re.ld',
  copy: true
)

# Include directories
inc_dirs = include_directories(
  '.',
  'rtos',
  'libopencm3/include'
)

# Library paths relative to source root
libopencm3_dir = meson.project_source_root() / 'libopencm3'
libopencm3_lib_dir = libopencm3_dir / 'lib'

# Verify libopencm3 exists using built-in functions
libopencm3_lib = libopencm3_lib_dir / 'libopencm3_stm32f4.a'
if not import('fs').exists(libopencm3_lib)
  error('libopencm3_stm32f4.a not found in ' + libopencm3_lib_dir)
endif

# Cross compilation specific settings
if meson.is_cross_build()
  add_project_arguments(
    # ARM architecture flags
    '-mcpu=cortex-m4',
    '-mthumb',
    '-mfloat-abi=hard',
    '-mfpu=fpv4-sp-d16',
    
    # Optimization and debug flags
    '-Os',
    '-ggdb3',
    '-std=c99',
    
    # Warning flags
    '-Wall',
    '-Wextra',
    '-Wshadow',
    '-Wimplicit-function-declaration',
    '-Wredundant-decls',
    '-Wmissing-prototypes',
    '-Wstrict-prototypes',
    '-Wundef',
    
    # Code generation flags
    '-fno-common',
    '-ffunction-sections',
    '-fdata-sections',
    '-MD',
    
    # Preprocessor definitions
    '-DSTM32F4',
    '-DSTM32F401RE',
    '-DSTM32F401xx',
    language: 'c'
  )

  add_project_link_arguments(
    '-nostartfiles',
    '-T' + meson.current_build_dir() / 'generated.stm32f401re.ld',
    '-Wl,-Map=main.map',
    '-Wl,--cref',
    '-Wl,--gc-sections',
    '-L' + libopencm3_lib_dir, 
    '-lopencm3_stm32f4',
    '-L/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/lib/thumb/v7e-m+fp/hard/', 
    '-Wl,--start-group',
    '-lc',
    '-lgcc',
    '-lnosys',
    '-Wl,--end-group',
    '-mfloat-abi=hard',
    '-mfpu=fpv4-sp-d16',
    language: 'c'
  )
endif

# Source files
src_files = [
  'app.c',
  'font.c',
  'gpio.c',
  'logo.c',
  'main.c',
  'ssd1339.c',
  'system.c',
  'rtos/heap_4.c',
  'rtos/list.c',
  'rtos/port.c',
  'rtos/queue.c',
  'rtos/tasks.c',
  'rtos/opencm3_shim.c',
]

# Build the ELF file
elf = executable('main.elf', src_files,
  include_directories : inc_dirs,
  build_by_default : true
)

# Create binary file from ELF
bin = custom_target('main.bin',
  input : elf,
  output : 'main.bin',
  command : [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
  build_by_default : true
)

# Optional: Add size reporting
run_target('size',
  command : [size, elf],
  depends : elf)