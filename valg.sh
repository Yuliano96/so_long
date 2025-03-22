valgrind --leak-check=full --show-leak-kinds=all --log-file=test.txt ./so_long map/map1.ber

# int	check_invalid_items(char s)
# {
# 	if (s != '1' && s != '0' && s != 'E' && s != 'P' && s != 'C' && s != '\n')
# 	{
# 		return (0);
# 	}
# 	return (1);
# }