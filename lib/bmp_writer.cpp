
#include "bmp_writer.h"


uint8_t GetColor(uint64_t grains) {
    switch (grains) {
        case 0: return 15;  //white
        case 1: return 2;   //green
        case 2: return 11;  //yellow
        case 3: return 12;  //purple
        default: return 0;  //black
    }
}

void WriteToBmp(const SandMap& pixels, const char* file_name) {
    std::ofstream fout(file_name, std::ios_base::binary | std::ios_base::out);
    if (!fout.is_open()) {
        std::cerr << "file " << file_name << " can't be open\n";
        exit(1);
    }

    const uint32_t bmp_header_size = 14;
    const uint32_t dib_header_size = 40;
    const uint8_t bits_per_pixel = 4;
    uint32_t width = pixels[0].size();
    uint32_t height = pixels.size();
    uint32_t databytes = height * ((bits_per_pixel * width + 31) / 32) * 4;
    //Must be equal to 2^bits_per_pixel
    uint32_t palette_size = 16;

    auto WriteBytes = [&](auto val) {
        for (int32_t i = sizeof(val); i > 0; --i) {
            fout << (uint8_t)(val);
            val >>= 8;
        }
    };

    //Header
    WriteBytes(static_cast<uint16_t>(0x42 + 0x4D * 256));
    //Size of bmp
    WriteBytes(databytes + bmp_header_size + dib_header_size + 4 * palette_size);
    WriteBytes(0);
    WriteBytes(54 + 4 * palette_size);

    //DIB Header
    WriteBytes(0x28);
    //Width
    WriteBytes(width);
    //Height
    WriteBytes(height);
    WriteBytes(static_cast<uint16_t>(0x01));
    //bit per pixel
    WriteBytes(static_cast<uint16_t>(bits_per_pixel));
    WriteBytes(0);
    //Size of the raw bitmap data (including padding)
    WriteBytes(databytes);
    WriteBytes(0x13 + 0x0B * 256);
    WriteBytes(0x13 + 0x0B * 256);
    WriteBytes(palette_size);
    WriteBytes(0);

    uint32_t palette[] = {
         0x000000 //Black
        ,0x005500 //Dark Green
        ,0x00aa00 //Contrast Green
        ,0x00ff00 //Light Green
        ,0x0000ff //Dark Blue
        ,0x0055ff //Light
        ,0x00aaff //Blue as a sky
        ,0x00ffff //Cyan
        ,0xff0000 //Red
        ,0xff5500 //Light Red
        ,0xffaa00 //Orange
        ,0xffff00 //Yellow
        ,0xff00ff //Purple
        ,0xff55ff //Light Purple
        ,0xffaaff //Pink
        ,0xffffff //White
    };

    for (int32_t i = 0; i < palette_size; ++i) {
        WriteBytes(palette[i]);
    }
    
    for (int32_t i = height - 1; i >= 0; --i) {
        int32_t bits = 0;
        uint8_t current_byte = 0;
        for (int32_t j = 0; j < width; ++j) {
            current_byte = current_byte * palette_size + GetColor(pixels[i][j]) % palette_size;
            bits += bits_per_pixel;
            if (bits % 8 == 0) {
                fout << current_byte;
                current_byte = 0;
            }
        }
        //Padding
        int bits_needed = databytes * 8 / height - bits;
        while (bits_needed > 0) {
            bits_needed -= bits_per_pixel;
            current_byte = current_byte * palette_size + 0;
            bits += bits_per_pixel;
            if (bits % 8 == 0) {
                fout << current_byte;
                current_byte = 0;
            }
        }
    }
}
