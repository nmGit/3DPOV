def data_to_packets(image, data_type, data_block_size):
    # Turn the data into packets of the form:
    # SECTOR: PACKET TYPE | SEQUENCE # | DATA                             | CHECKSUM
    # BYTE:  1   2   3   4      5       6  7  8  9  10 11     51  52  53       54
    #     ------------------------------------------------------------------------
    #     | 'I' 'M' 'G' '\0' || seq# || R0 G0 B0 R1 G1 B1 ... R15 G15 B15 || checksum |
    #     ------------------------------------------------------------------------
    #
    # The packet above is just an example showing how an image packet looks
    # The first three bytes spell "IMG" with a null terminator
    # Where each packet will contain one row (16 RGB pixes = number of leds)
    # Where checksum = (uint8_t) SUM[R0 G0 B0 R1 G1 B1 ... R15 G15 B15]
    # Sequence number is the column number (0-99)

    packet_type = [ord(chr) for chr in data_type]
    packet_type.append(0) #add null terminator
    packets = []

    for seq, packet in enumerate(image[0:len(image):data_block_size]):
        packet = []
        # We now construct the packet in steps
        # Step 1: Each packet starts with the packet type (i.e. 'IMG')
        packet.extend(packet_type)
        # Step 2: Add a fin and sequence number
        packet.append(0)
        packet.append(seq)
        # Step 3: Add data (16 pixels x 3 bytes (RGB) per pixel)
        #print image[seq:(seq + data_block_size)]
        packet_data = [byte for byte in image[seq*data_block_size:(seq*data_block_size + data_block_size)]]
        #print seq
        packet.extend(packet_data)
        # Step 4: Generate checksum. Should also be 1 byte, hence the and with 0xFF
        packet.append(sum(packet_data) & 0xFF)
        packets.append(packet)
    return packets
