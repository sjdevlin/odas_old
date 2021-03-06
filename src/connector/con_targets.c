
    /**
    * \file     con_targets.c
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

    #include <connector/con_targets.h>

    con_targets_obj * con_targets_construct(const unsigned int nOuts, const msg_targets_cfg * msg_targets_config) {

        con_targets_obj * obj;
        unsigned int iOut;

        obj = (con_targets_obj *) malloc(sizeof(con_targets_obj));

        obj->nOuts = nOuts;

        obj->in = msg_targets_construct(msg_targets_config);

        obj->outs = (msg_targets_obj **) malloc(sizeof(msg_targets_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_targets_construct(msg_targets_config);
        }

        return obj;    

    }

    void con_targets_destroy(con_targets_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_targets_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_targets_destroy(obj->in);

        free((void *) obj);

    }

    int con_targets_process(con_targets_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_targets_copy(obj->outs[iOut], obj->in);
        }

        if (msg_targets_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }
