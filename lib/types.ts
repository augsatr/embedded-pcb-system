export type MandiPrice = {
  market: string; district: string; commodity: string; variety: string;
  modalPrice: number; minPrice: number; maxPrice: number; arrivalQty: number; trend: "up"|"down"|"stable"; distanceKm: number;
};
export type Buyer = {
  id: string; name: string; type: "Processor"|"Retailer"|"Exporter"|"FPO"|"Institutional";
  commodity: string; requiredQty: number; offerPrice: number; qualityGrade: string; verified: boolean; rating: number; location: string;
};
export type Lot = { id: string; farmer: string; fpo?: string; commodity: string; qty: number; grade: string; status: "Ready"|"Graded"|"Listed"|"Sold"; priceAsk: number; };
export type ForecastPoint = { date: string; price: number; predicted?: number; volume: number; };
