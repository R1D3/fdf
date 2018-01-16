#include "fdf.h"

char   *ft_split(char *str, char c)
{
    char *newstr;
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    while (str[j++])
        if (str[j] == c)
            i++;
    newstr = ft_memalloc(sizeof(ft_strlen(str - i)));
    j = 0;
    k = 0;
    while (str[j])
    {
        if (str[j] == c)
            j++;
        newstr[k] = str[j];
        k++;
        j++;
    }
    newstr[k] = '\0';
    return (newstr);
}

t_element *addback(t_element *list, void *x)
{
    t_element *new;
    t_element *tmp;
    if (!(new = ft_memalloc(sizeof(*new))))
        exit(0);
    new->content = x;
    new->next = NULL;
    if (list == NULL)
        return (new);
    else
        tmp = list;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return(list);
}


void    printlist(t_element *list)
{
    t_element *tmp;
    tmp = list;
    if (tmp == NULL)
        printf("liste vide");
    while (tmp != NULL)
        {
            printf("%s\n", tmp->content);
            tmp = tmp->next;
        }
}

int main(int ac, char **av)
{
    t_element *liste;
    t_env a;

    if (ac == 2)
    {
        a.file = av[1];
        a.fd = open(a.file, O_RDONLY);
        while (get_next_line(a.fd, &a.line) == 1)
            {
                liste = addback(liste, ft_split(a.line, ' '));
            }
        printlist(liste);
    }
    else
        printf("usage : fdf need file");

}
