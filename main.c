#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Please specify input file\n");
        return 1;
    }

    AVFormatContext *formatContext = NULL;
    if (avformat_open_input(&formatContext, argv[1], NULL, NULL) != 0) {
        fprintf(stderr, "Failed to open input file...\n");
        return 2;
    }

    if (avformat_find_stream_info(formatContext, NULL) < 0) {
        fprintf(stderr, "Failed to find stream info...\n");
        return 3;
    }

    av_dump_format(formatContext, 0, argv[1], 0);

    AVPacket packet;
    int64_t* last_ptses = calloc(formatContext->nb_streams, sizeof(int64_t));
    for (int i = 0; i < formatContext->nb_streams; i++) {
        last_ptses[i] = 0;
    }
    while (av_read_frame(formatContext, &packet) >= 0) {
        printf("Packet: stream_index=%d, pts=%ld, diff=%ld\n", packet.stream_index, packet.pts, packet.pts - last_ptses[packet.stream_index]);
        last_ptses[packet.stream_index] = packet.pts;
        av_packet_unref(&packet);
    }
    return 0;
}