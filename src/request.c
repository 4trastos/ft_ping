#include "ft_ping.h"

// **Creación paquete ICMP** + checksum

int     icmp_creation(struct config *conf)
{
    if (conf->packet == NULL)
    {
        conf->packet = malloc(sizeof(struct ping_packet));
        if (!conf->packet)
            return (-1);
    }

    conf->sequence++;
    conf->packet->icmp_hdr.type = 8;                      // (ECHO_REQUEST)
    conf->packet->icmp_hdr.code = 0;
    conf->packet->icmp_hdr.checksum = 0;
    conf->packet->icmp_hdr.un.echo.id = getpid();
    conf->packet->icmp_hdr.un.echo.sequence = conf->sequence;
    gettimeofday(&conf->packet->timestamp, NULL);
    memset(conf->packet->data, 0, 48);

    conf->packet->icmp_hdr.checksum = calculate_checksum(conf->packet,sizeof(struct ping_packet));

    return (0);
}

uint16_t    calculate_checksum(void *packet, size_t len)
{
    uint32_t    sum = 0;
    uint16_t    *aux = packet;

    for (size_t i = 0; i < len / 2; i++)            // Sumamos todos los words de 16 bits
        sum += aux[i];
    
    if (len % 2)                                    // Si es impar añadimos un bite al final
        sum += ((uint8_t*)packet)[len - 1];

    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    
    return (~sum);                                  // Invertir todos los bits
}

// 0800 0000 0001 0001 Paquete pequeño

//    0800 = type(8) + code(0)

//    0000 = checksum (temporalmente 0)

//    0001 = id(1)

//    0001 = sequence(1)