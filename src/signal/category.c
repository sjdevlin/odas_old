
   /**
    * \file     category.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <signal/category.h>

    categories_obj * categories_construct_zero(const unsigned int nSignals) {

        categories_obj * obj;

        obj = (categories_obj *) malloc(sizeof(categories_obj));

        obj->nSignals = nSignals;
// For meet pie
        obj->angle_xy_array = (unsigned int *) malloc(sizeof(unsigned int) * nSignals);
        memset(obj->angle_xy_array, 0x00, sizeof(unsigned int) * nSignals);
        obj->frequency_array = (float *) malloc(sizeof(float) * nSignals);
        memset(obj->frequency_array, 0x00, sizeof(float) * nSignals);
        obj->energy_array = (float *) malloc(sizeof(float) * nSignals);
        memset(obj->energy_array, 0x00, sizeof(float) * nSignals);
//
        obj->array = (char *) malloc(sizeof(char) * nSignals);
        memset(obj->array, 0x00, sizeof(char) * nSignals);

        return obj;

    }

    void categories_destroy(categories_obj * obj) {

//For meet pie
        free((void *) obj->angle_xy_array);
        free((void *) obj->frequency_array);
        free((void *) obj->energy_array);
        //
        free((void *) obj->array);
        free((void *) obj);

    }

    void categories_copy(categories_obj * dest, const categories_obj * src) {

// For meet pie
        memcpy(dest->angle_xy_array, src->angle_xy_array, sizeof(unsigned int) * src->nSignals);
        memcpy(dest->frequency_array, src->frequency_array, sizeof(float) * src->nSignals);
        memcpy(dest->energy_array, src->energy_array, sizeof(float) * src->nSignals);
//
        memcpy(dest->array, src->array, sizeof(char) * src->nSignals);

    }

    void categories_zero(categories_obj * obj) {

// For meet pie
        memset(obj->angle_xy_array, 0x00, sizeof(unsigned int) * obj->nSignals);
        memset(obj->frequency_array, 0x00, sizeof(float) * obj->nSignals);
        memset(obj->energy_array, 0x00, sizeof(float) * obj->nSignals);
//
        memset(obj->array, 0x00, sizeof(char) * obj->nSignals);

    }

    void categories_printf(const categories_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %c\n",iSignal,obj->array[iSignal]);

        }

    }
