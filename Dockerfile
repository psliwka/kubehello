FROM alpine:latest
RUN apk --no-cache add binutils gcc musl-dev
ADD main.c .
RUN x86_64-alpine-linux-musl-gcc -Wall -Wextra -Werror -pedantic-errors -static -Os main.c -o kubehello
RUN strip --strip-all kubehello

FROM scratch
COPY --from=0 kubehello /bin/
ENTRYPOINT ["/bin/kubehello"]
USER 1000:1000
