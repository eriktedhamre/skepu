According to the Bringing Parsec out of the corner article fluidanimate can be transformed into 9 sequential maps.

TBB version
They have a ((XDIVS) * (ZDIVS)) vector containing the datatype Grid.

Serial version
Only uses the Cells data type with int nx, ny, nz; to list the number of cells in each direction.

Init Simulation() does the following

Initializes a new cell list
nz, ny, nx = ck, cj, ci Coordinates of cells inrelation to dimension sizes
Calculates the destination coordinates for each particle in each cell (double for-loop)

I think there is a one dimensional index from
int index = (ck*ny + cj)*nx + ci;
int np = cnumPars[index];
// Do not really understand this.
// I think it simply loops until it finds a non-full cell at the specified index
// If all cells are full more are allocated, which I do not really understand, since we do a lot of pre-allocating // but that might simply be to save time
while(np > PARTICLES_PER_CELL) {
    cell = cell->next;
    np = np - PARTICLES_PER_CELL;
}

// I think this line means that cnumPars is an array that lists the number of particles at each nx, ny, nz coordinate
++cnumPars[index];

The ROI consists of these four functions

RebuildGrid();
ComputeForces();
ProcessCollisions();
AdvanceParticles();

RebuildGrid();

swap src and dst arrays (1 MAP)
Resets the destinations cell-linked lists (1 MAP)
Then performs the move of all the particles to their appropriate cell, (1 MAP)
new linked lists at each coordinate is constructed. (1 MAP)
Returns unused cells to the cell pool.

ComputeForces();

for each cell and each particle within that cell, find the neighboring cells (1 MAP)
For each particle in each neighbour calculate how it affects the current particle. (1 MAP)
Then I think a second loop that calculates how the internal particles affect each other. (1 MAP)
Then calculate the acceleration of each particle (1 MAP)


ProcessCollisions()
It seems to be collisions between the particles and the walls of the container. (1 MAP)
So no collisions between particles.

AdvanceParticles()
Advances all the particles in regard to their speed.




Based on the TBB-implementation 
I assume one GridLauncher can be converted into a SkePU-Map call.
This would result in 9 Maps to complete one iteration of the ROI, 8 if USE_ImprenetableWall is enabled.
