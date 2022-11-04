#include <stdio.h>
#include <unistd.h>

#define MAX_K8S_NS_LEN 254 // 253 as defined by K8s spec, plus the final \0

const char* get_k8s_ns() {
  static char buffer[MAX_K8S_NS_LEN];
  FILE* nsfile = fopen("/var/run/secrets/kubernetes.io/serviceaccount/namespace", "r");
  if (!nsfile) return NULL;
  char* result = fgets(buffer, MAX_K8S_NS_LEN, nsfile);
  fclose(nsfile);
  return result;
}

int main() {
  const char* ns = get_k8s_ns();
  if (ns) {
    printf("Hello from %s!\n", ns);
    pause();
  } else {
    perror("Could not read current Kubernetes namespace");
    return (1);
  }
}
