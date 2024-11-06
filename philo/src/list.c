/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:35:56 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 13:38:41 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_lista	*create_list(void)
{
	return (NULL);
}

t_lista	*insert(t_lista *l, int id, t_lista *aux)
{
	t_lista	*new;

	new = (t_lista *)malloc(sizeof(t_lista));
	if (!new)
		return (NULL);
	new->ant = NULL;
	new->prox = NULL;
	new->id = id;
	if (l)
	{
		aux = l;
		while (aux->prox != l)
			aux = aux->prox;
		aux->prox = new;
		new->ant = aux;
		new->prox = l;
		l->ant = new;
	}
	else
	{
		new->prox = new;
		new->ant = new;
		l = new;
	}
	return (l);
}

t_lista	*delete_list(t_lista *l)
{
	t_lista	*aux;
	t_lista	*prox;
	t_lista	*first;

	if (!l)
		return (NULL);
	first = l;
	aux = l->prox;
	while (aux != first)
	{
		prox = aux->prox;
		free(aux);
		aux = prox;
	}
	free(first);
	return (NULL);
}
