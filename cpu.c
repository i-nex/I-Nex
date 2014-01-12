#include <stdio.h>
#include <libcpuid.h>

int main(void)
{
	if (!cpuid_present()) {                                                // check for CPUID presence
		printf("Sorry, your CPU doesn't support CPUID!\n");
		return -1;
	}
	struct cpu_raw_data_t raw;                                             // contains only raw data
	struct cpu_id_t data;                                                  // contains recognized CPU features data
	if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
		printf("Sorry, cannot get the CPUID raw data.\n");
		printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
		return -2;
	}
	if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
		printf("Sorrry, CPU identification failed.\n");
		printf("Error: %s\n", cpuid_error());
		return -3;
	}
	//printf("CPU clock is: %d MHz (according to your OS)\n", cpu_clock_by_os()); // print out the CPU clock, according to the OS
	//printf("CPU clock is: %d MHz (tested)\n", cpu_clock_measure(200, 0));  // print out the CPU clock, measured with RDTSC.
	//printf("CPUID Library Version: `%s'\n", cpuid_lib_version());
	//printf("Found: %s CPU\n", data.vendor_str);                            // print out the vendor string (e.g. `GenuineIntel')
	//printf("Processor model is `%s'\n", data.cpu_codename);                // print out the CPU code name (e.g. `Pentium 4 (Northwood)')
	//printf("The full brand string is `%s'\n", data.brand_str);             // print out the CPU brand string
	//printf("The processor has %dK L1 cache and %dK L2 cache and %dK L3\n", data.l1_data_cache, data.l2_cache, data.l3_cache); // print out cache size information
	//printf("Processor family is `%d'\n", data.family);
	//printf("The processor has %d cores and %d logical processors\n", data.num_cores, data.num_logical_cpus); // print out CPU cores information
	//printf("Supported multimedia instruction sets:\n");
	printf("{\"FLAGS\":  [\n");
	printf("{\n");
	printf("\"CPU_FEATURE_MMX\": %s\n", data.flags[CPU_FEATURE_MMX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MMXEXT\": %s\n", data.flags[CPU_FEATURE_MMXEXT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE\": %s\n", data.flags[CPU_FEATURE_SSE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE2\": %s\n", data.flags[CPU_FEATURE_SSE2] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_3DNOW\": %s\n", data.flags[CPU_FEATURE_3DNOW] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_HT\": %s\n", data.flags[CPU_FEATURE_HT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FPU\": %s\n", data.flags[CPU_FEATURE_FPU] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_VME\": %s\n", data.flags[CPU_FEATURE_VME] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CLFLUSH\": %s\n", data.flags[CPU_FEATURE_CLFLUSH] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSSE3\": %s\n", data.flags[CPU_FEATURE_SSSE3] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_LM\": %s\n", data.flags[CPU_FEATURE_LM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_LAHF_LM\": %s\n", data.flags[CPU_FEATURE_LAHF_LM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MTRR\": %s\n", data.flags[CPU_FEATURE_MTRR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_ACPI\": %s\n", data.flags[CPU_FEATURE_ACPI] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_VMX\": %s\n", data.flags[CPU_FEATURE_VMX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SYSCALL\": %s\n", data.flags[CPU_FEATURE_SYSCALL] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_DTS64\": %s\n", data.flags[CPU_FEATURE_DTS64] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FPU\": %s\n", data.flags[CPU_FEATURE_FPU] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_VME\": %s\n", data.flags[CPU_FEATURE_VME] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_DE\": %s\n", data.flags[CPU_FEATURE_DE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PSE\": %s\n", data.flags[CPU_FEATURE_PSE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TSC\": %s\n", data.flags[CPU_FEATURE_TSC] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MSR\": %s\n", data.flags[CPU_FEATURE_MSR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PAE\": %s\n", data.flags[CPU_FEATURE_PAE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MCE\": %s\n", data.flags[CPU_FEATURE_MCE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CX8\": %s\n", data.flags[CPU_FEATURE_CX8] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_APIC\": %s\n", data.flags[CPU_FEATURE_APIC] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MTRR\": %s\n", data.flags[CPU_FEATURE_MTRR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SEP\": %s\n", data.flags[CPU_FEATURE_SEP] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PGE\": %s\n", data.flags[CPU_FEATURE_PGE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MCA\": %s\n", data.flags[CPU_FEATURE_MCA] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CMOV\": %s\n", data.flags[CPU_FEATURE_CMOV] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PAT\": %s\n", data.flags[CPU_FEATURE_PAT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PSE36\": %s\n", data.flags[CPU_FEATURE_PSE36] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PN\": %s\n", data.flags[CPU_FEATURE_PN] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CLFLUSH\": %s\n", data.flags[CPU_FEATURE_CLFLUSH] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_DTS\": %s\n", data.flags[CPU_FEATURE_DTS] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_ACPI\": %s\n", data.flags[CPU_FEATURE_ACPI] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FXSR\": %s\n", data.flags[CPU_FEATURE_FXSR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE\": %s\n", data.flags[CPU_FEATURE_SSE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE2\": %s\n", data.flags[CPU_FEATURE_SSE2] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SS\": %s\n", data.flags[CPU_FEATURE_SS] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_HT\": %s\n", data.flags[CPU_FEATURE_HT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TM\": %s\n", data.flags[CPU_FEATURE_TM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_IA64\": %s\n", data.flags[CPU_FEATURE_IA64] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PBE\": %s\n", data.flags[CPU_FEATURE_PBE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PNI\": %s\n", data.flags[CPU_FEATURE_PNI] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PCLMUL\": %s\n", data.flags[CPU_FEATURE_PCLMUL] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MONITOR\": %s\n", data.flags[CPU_FEATURE_MONITOR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_DS_CPL\": %s\n", data.flags[CPU_FEATURE_DS_CPL] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_VMX\": %s\n", data.flags[CPU_FEATURE_VMX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SMX\": %s\n", data.flags[CPU_FEATURE_SMX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_EST\": %s\n", data.flags[CPU_FEATURE_EST] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TM2\": %s\n", data.flags[CPU_FEATURE_TM2] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSSE3\": %s\n", data.flags[CPU_FEATURE_SSSE3] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CID\": %s\n", data.flags[CPU_FEATURE_CID] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CX16\": %s\n", data.flags[CPU_FEATURE_CX16] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_XTPR\": %s\n", data.flags[CPU_FEATURE_XTPR] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_PDCM\": %s\n", data.flags[CPU_FEATURE_PDCM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_DCA\": %s\n", data.flags[CPU_FEATURE_DCA] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE4_1\": %s\n", data.flags[CPU_FEATURE_SSE4_1] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE4_2\": %s\n", data.flags[CPU_FEATURE_SSE4_2] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SYSCALL\": %s\n", data.flags[CPU_FEATURE_SYSCALL] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_XD\": %s\n", data.flags[CPU_FEATURE_XD] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MOVBE\": %s\n", data.flags[CPU_FEATURE_MOVBE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_POPCNT\": %s\n", data.flags[CPU_FEATURE_POPCNT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_AES\": %s\n", data.flags[CPU_FEATURE_AES] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_XSAVE\": %s\n", data.flags[CPU_FEATURE_XSAVE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_OSXSAVE\": %s\n", data.flags[CPU_FEATURE_OSXSAVE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_AVX\": %s\n", data.flags[CPU_FEATURE_AVX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MMXEXT\": %s\n", data.flags[CPU_FEATURE_MMXEXT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_3DNOW\": %s\n", data.flags[CPU_FEATURE_3DNOW] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_3DNOWEXT\": %s\n", data.flags[CPU_FEATURE_3DNOWEXT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_NX\": %s\n", data.flags[CPU_FEATURE_NX] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FXSR_OPT\": %s\n", data.flags[CPU_FEATURE_FXSR_OPT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_RDTSCP\": %s\n", data.flags[CPU_FEATURE_RDTSCP] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_LM\": %s\n", data.flags[CPU_FEATURE_LM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_LAHF_LM\": %s\n", data.flags[CPU_FEATURE_LAHF_LM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CMP_LEGACY\": %s\n", data.flags[CPU_FEATURE_CMP_LEGACY] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SVM\": %s\n", data.flags[CPU_FEATURE_SVM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE4A\": %s\n", data.flags[CPU_FEATURE_SSE4A] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_MISALIGNSSE\": %s\n", data.flags[CPU_FEATURE_MISALIGNSSE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_ABM\": %s\n", data.flags[CPU_FEATURE_ABM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_3DNOWPREFETCH\": %s\n", data.flags[CPU_FEATURE_3DNOWPREFETCH] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_OSVW\": %s\n", data.flags[CPU_FEATURE_OSVW] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_IBS\": %s\n", data.flags[CPU_FEATURE_IBS] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SSE5\": %s\n", data.flags[CPU_FEATURE_SSE5] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_SKINIT\": %s\n", data.flags[CPU_FEATURE_SKINIT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_WDT\": %s\n", data.flags[CPU_FEATURE_WDT] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TS\": %s\n", data.flags[CPU_FEATURE_TS] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FID\": %s\n", data.flags[CPU_FEATURE_FID] ? "True\"," : "0 ,");
	printf("\"CPU_FEATURE_VID\": %s\n", data.flags[CPU_FEATURE_VID] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TTP\": %s\n", data.flags[CPU_FEATURE_TTP] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TM_AMD\": %s\n", data.flags[CPU_FEATURE_TM_AMD] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_STC\": %s\n", data.flags[CPU_FEATURE_STC] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_100MHZSTEPS\": %s\n", data.flags[CPU_FEATURE_100MHZSTEPS] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_HWPSTATE\": %s\n", data.flags[CPU_FEATURE_HWPSTATE] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_CONSTANT_TSC\": %s\n", data.flags[CPU_FEATURE_CONSTANT_TSC] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_XOP\": %s\n", data.flags[CPU_FEATURE_XOP] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FMA3\": %s\n", data.flags[CPU_FEATURE_FMA3] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_FMA4\": %s\n", data.flags[CPU_FEATURE_FMA4] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_TBM\": %s\n", data.flags[CPU_FEATURE_TBM] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_F16C\": %s\n", data.flags[CPU_FEATURE_F16C] ? "1 ," : "0 ,");
	printf("\"CPU_FEATURE_RDRAND\": %s\n", data.flags[CPU_FEATURE_RDRAND] ? "1 " : "0 ");
	printf("}\n]}}\n");
	return 0;
}