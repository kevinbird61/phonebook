#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("perf_orig.log", "r");
    FILE *output = fopen("output_cache.txt", "w");
    // orig version
    if (!fp) {
        printf("ERROR opening input file perf_orig.log\n");
        exit(0);
    }
    int orig_result,opt_result,strcp_result;
    char dump[1024];
    fscanf(fp, "%d%s\n",&orig_result,dump);
    fclose(fp);

    // opt version
    fp = fopen("perf_opt.log","r");
    if (!fp) {
        printf("ERROR opening input file perf_opt.log\n");
        exit(0);
    }
    fscanf(fp, "%d%s\n" , &opt_result , dump);
    fclose(fp);

    // strcp version
    fp = fopen("perf_strcp.log","r");
    if (!fp) {
        printf("ERROR opening input file perf_strcp.log\n");
        exit(0);
    }
    fscanf(fp, "%d%s\n" , &strcp_result , dump);

    fprintf(output, "cache-misses %d %d %d\n",orig_result,opt_result,strcp_result);

    fclose(output);
    fclose(fp);
    return 0;
}
