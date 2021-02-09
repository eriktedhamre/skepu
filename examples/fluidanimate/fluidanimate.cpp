#include <iostream>
#include <cmath>
#include <list>

#include <skepu>


#define PARTICLES_PER_CELL = 16


std::vector<int> cells, cells2;
std::vector<int> cnumPars, cnumPars2;

////////////////////////////////////////////////////////////////////////////////

/*
void ClearParticlesMT(int tid)
{
  for(int iz = grids[tid].sz; iz < grids[tid].ez; ++iz)
    for(int iy = grids[tid].sy; iy < grids[tid].ey; ++iy)
      for(int ix = grids[tid].sx; ix < grids[tid].ex; ++ix)
      {
        int index = (iz*ny + iy)*nx + ix;
        cnumPars[index] = 0;
		cells[index].next = NULL;
        last_cells[index] = &cells[index];
      }
}
*/
// Resets the cnumPars and cells arrays
void ClearParticles()
{
    int index;
    cnumPars[index] = 0;
	  cells[index].next = NULL;
    last_cells[index] = &cells[index];
}


////////////////////////////////////////////////////////////////////////////////


void RebuildGrid()
{

    int index2 = (iz*ny + iy)*nx + ix;
    Cell *cell2 = &cells2[index2];
    int np2 = cnumPars2[index2];
    //iterate through source particles
    for(int j = 0; j < np2; ++j)
    {
    //get destination for source particle
    int ci = (int)((cell2->p[j % PARTICLES_PER_CELL].x - domainMin.x) / delta.x);
    int cj = (int)((cell2->p[j % PARTICLES_PER_CELL].y - domainMin.y) / delta.y);
    int ck = (int)((cell2->p[j % PARTICLES_PER_CELL].z - domainMin.z) / delta.z);

    //confine to domain if necessary ERIK
    if(ci < 0) ci = 0; else if(ci > (nx-1)) ci = nx-1;
    if(cj < 0) cj = 0; else if(cj > (ny-1)) cj = ny-1;
    if(ck < 0) ck = 0; else if(ck > (nz-1)) ck = nz-1;
    #if 0
		  assert(ci>=ix-1);
		  assert(ci<=ix+1);
		  assert(cj>=iy-1);
		  assert(cj<=iy+1);
		  assert(ck>=iz-1);
		  assert(ck<=iz+1);
#endif
#ifdef ENABLE_CFL_CHECK
          //check that source cell is a neighbor of destination cell
          bool cfl_cond_satisfied=false;
          for(int di = -1; di <= 1; ++di)
            for(int dj = -1; dj <= 1; ++dj)
              for(int dk = -1; dk <= 1; ++dk)
              {
                int ii = ci + di;
                int jj = cj + dj;
                int kk = ck + dk;
                if(ii >= 0 && ii < nx && jj >= 0 && jj < ny && kk >= 0 && kk < nz)
                {
                  int index = (kk*ny + jj)*nx + ii;
                  if(index == index2)
                  {
                    cfl_cond_satisfied=true;
                    break;
                  }
                }
              }
          if(!cfl_cond_satisfied)
          {
            std::cerr << "FATAL ERROR: Courant–Friedrichs–Lewy condition not satisfied." << std::endl;
            exit(1);
          }
#endif //ENABLE_CFL_CHECK

          // Find destination cell ERIK
          int index = (ck*ny + cj)*nx + ci;
          // this assumes that particles cannot travel more than one grid cell per time step

          // Checks if the current cell is on the border to another grid point ERIK
          // If it is locks the cell ERIK
          if(border[index])
            pthread_mutex_lock(&mutex[index][CELL_MUTEX_ID]);
          Cell *cell = last_cells[index];
          int np = cnumPars[index];

          //add another cell structure if everything full
          if( (np % PARTICLES_PER_CELL == 0) && (cnumPars[index] != 0) ) {
            cell->next = cellpool_getcell(&pools[tid]);
            cell = cell->next;
            last_cells[index] = cell;
          }
          ++cnumPars[index];
          if(border[index])
            pthread_mutex_unlock(&mutex[index][CELL_MUTEX_ID]);

          //copy source to destination particle
          
          cell->p[np % PARTICLES_PER_CELL]  = cell2->p[j % PARTICLES_PER_CELL];
          cell->hv[np % PARTICLES_PER_CELL] = cell2->hv[j % PARTICLES_PER_CELL];
          cell->v[np % PARTICLES_PER_CELL]  = cell2->v[j % PARTICLES_PER_CELL];
          //move pointer to next source cell in list if end of array is reached
          if(j % PARTICLES_PER_CELL == PARTICLES_PER_CELL-1) {
            Cell *temp = cell2;
            cell2 = cell2->next;
            //return cells to pool that are not statically allocated head of lists
            if(temp != &cells2[index2]) {
              //NOTE: This is thread-safe because temp and pool are thread-private, no need to synchronize
              cellpool_returncell(&pools[tid], temp);
            }
          }
        } // for(int j = 0; j < np2; ++j)
        //return cells to pool that are not statically allocated head of lists
        if((cell2 != NULL) && (cell2 != &cells2[index2])) {
          cellpool_returncell(&pools[tid], cell2);
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

// Sets cell->density to 0 for all particles
// Sets cell->a = externalAcceleration; for all particles
void InitDensitiesAndForcesMT(int tid)
{
  for(int iz = grids[tid].sz; iz < grids[tid].ez; ++iz)
    for(int iy = grids[tid].sy; iy < grids[tid].ey; ++iy)
      for(int ix = grids[tid].sx; ix < grids[tid].ex; ++ix)
      {
                    int index = (iz*ny + iy)*nx + ix;
        Cell *cell = &cells[index];
        int np = cnumPars[index];
        for(int j = 0; j < np; ++j)
        {
          cell->density[j % PARTICLES_PER_CELL] = 0.0;
          cell->a[j % PARTICLES_PER_CELL] = externalAcceleration;
          //move pointer to next cell in list if end of array is reached
          if(j % PARTICLES_PER_CELL == PARTICLES_PER_CELL-1) {
            cell = cell->next;
          }
        }
      }
}

////////////////////////////////////////////////////////////////////////////////





// Trying to translate the Advance frame function from the pthreads implementation
void AdvanceFrame(){

    //swap src and dest arrays with particles
    std::swap(cells, cells2);
    std::swap(cnumPars, cnumPars2);
}




