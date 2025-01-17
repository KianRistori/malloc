#include "../include/malloc.h"

void	ft_putstr(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	ft_putnbr_base(unsigned long nb, const char *base)
{
	if (nb >= 16)
		ft_putnbr_base(nb / 16, base);
	write(1, &base[nb % 16], 1);
}

void	ft_putnbr(size_t nb)
{
	if (nb >= 10)
		ft_putnbr(nb / 10);
	char c = (nb % 10) + '0';
	write(1, &c, 1);
}

void	print_chunk(heapChunk_t *chunk_list, const char *zone_name)
{
	heapChunk_t *chunk = chunk_list;
	int first = 1;

	while (chunk)
	{
		if (chunk->inuse)
		{
			if (first)
			{
				ft_putstr(zone_name);
				ft_putstr(" : 0x");
				ft_putnbr_base((unsigned long)chunk, "0123456789ABCDEF");
				ft_putstr("\n");
				first = 0;
			}

			ft_putstr("0x");
			ft_putnbr_base((unsigned long)chunk, "0123456789ABCDEF");

			ft_putstr(" - 0x");

			ft_putnbr_base((unsigned long)((char*)chunk + chunk->size), "0123456789ABCDEF");

			ft_putstr(" : ");
			ft_putnbr(chunk->size);
			ft_putstr(" bytes\n");
		}

		chunk = chunk->next;
	}
}

void	calculate_total_memory(heapChunk_t *chunk, size_t *size)
{
	while (chunk)
	{
		if (chunk->inuse)
			*size += chunk->size;
		chunk = chunk->next;
	}
}

void	show_alloc_mem()
{
	extern heapInfo_t heap;
	size_t total_size = 0;

	if (heap.tiny)
	{
		print_chunk(heap.tiny->start, "TINY");
		heapChunk_t *chunk = heap.tiny->start;
		calculate_total_memory(chunk, &total_size);
	}

	if (heap.small)
	{
		print_chunk(heap.small->start, "SMALL");
		heapChunk_t *chunk = heap.small->start;
		calculate_total_memory(chunk, &total_size);
	}

	if (heap.large)
	{
		print_chunk(heap.large->start, "LARGE");
		heapChunk_t *chunk = heap.large->start;
		calculate_total_memory(chunk, &total_size);
	}

	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" bytes\n");
}

