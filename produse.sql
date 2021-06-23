DROP TYPE IF EXISTS marca;
DROP TYPE IF EXISTS tip_piesa;


CREATE TYPE marca AS ENUM('acura','audi','bmw','honda','hyundai','infiniti','isuzu','jaguar','kia','lexus','mazda','mercedes-benz','mitsubishi','nissan','saab','scion','subaru','suzuki','toyota','volkswagen','volvo');
CREATE TYPE tip_piesa AS ENUM('aftermarket', 'OE', 'OEM');

CREATE TABLE IF NOT EXISTS produse (
   id serial PRIMARY KEY,
   nume VARCHAR(300) UNIQUE NOT NULL,
   descriere TEXT,
   imagine VARCHAR(500),
   marca marca DEFAULT 'audi',
   tip tip_piesa DEFAULT 'OE',
   pret NUMERIC(8,2) NOT NULL,
   reducere NUMERIC(8,0) NULL,
   expira_oferta date NULL,
   culoare VARCHAR(40),

   stock BOOLEAN NOT NULL DEFAULT TRUE
);

select * from produse;