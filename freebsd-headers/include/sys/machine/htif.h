#define HTIF_DEV_SHIFT      (56)
#define HTIF_CMD_SHIFT      (48)

#define HTIF_CMD_READ       (0x00UL)
#define HTIF_CMD_WRITE      (0x01UL)
#define HTIF_CMD_IDENTIFY   (0xFFUL)

#define HTIF_MAX_DEV        (256)
#define HTIF_MAX_ID         (64)

#define HTIF_ALIGN          (64)

void htif_init(void);
void htif_test(void);

static inline void htif_tohost(unsigned long dev,
    unsigned long cmd, unsigned long data)
{
	unsigned long packet;

	packet = (dev << HTIF_DEV_SHIFT) | (cmd << HTIF_CMD_SHIFT) | data;
	while (csr_swap(mtohost, packet)) {
		//cpu_relax();
	}
}

static inline unsigned long __htif_fromhost(void)
{

	//unsigned long __v = (unsigned long)(0);
	//__asm __volatile("csrrw %0, mfromhost, %1" : "=r" (__v) : "i" (__v));
	//return (__v);

	return csr_swap(mfromhost, 0);
}

static inline unsigned long htif_fromhost(void)
{
	unsigned long data;

	while (!(data = __htif_fromhost())) {
		//cpu_relax();
	}

	return (data);
}
