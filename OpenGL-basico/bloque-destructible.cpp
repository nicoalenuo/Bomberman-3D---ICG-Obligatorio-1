class bloque_destructible {
	private:
		int posX;
		int posZ;

	public:
		bloque_destructible(int posX, int posZ) {
			(*this).posX = posX;
			(*this).posZ = posZ;
		}

		int getPosX() {
			return (*this).posX;
		}

		int getPosZ() {
			return (*this).posZ;
		}
};