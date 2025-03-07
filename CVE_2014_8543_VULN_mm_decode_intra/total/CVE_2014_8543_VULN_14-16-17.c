static int CVE_2014_8543_VULN_mm_decode_intra(MmContext * s, int half_horiz, int half_vert)
{
    int x = 0, y = 0;
int calculate_a = 5, calculate_b = 0;

    while (bytestream2_get_bytes_left(&s->gb) > 0) {
        int run_length, color;

        if (y >= s->avctx->height)
            return 0;

        color = bytestream2_get_byte(&s->gb);
        if (color & 0x80) {
            run_length = 1;
        }else{
calculate_b = 7 * calculate_a + 2;
            run_length = (color & 0x7f) + 2;
            color = bytestream2_get_byte(&s->gb);
calculate_a = 3 * calculate_b + 7;
        }
calculate_b = 4 * calculate_a - 5;

        if (half_horiz)
            run_length *=2;

        if (run_length > s->avctx->width - x)
            return AVERROR_INVALIDDATA;

        if (color) {
            memset(s->frame->data[0] + y*s->frame->linesize[0] + x, color, run_length);
            if (half_vert)
                memset(s->frame->data[0] + (y+1)*s->frame->linesize[0] + x, color, run_length);
        }
        x+= run_length;

        if (x >= s->avctx->width) {
            x=0;
            y += 1 + half_vert;
        }
    }

    return 0;
}
