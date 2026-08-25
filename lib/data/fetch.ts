import { AgmarknetRecord, API_KEY, API_BASE, cachedOnion, cachedOtherCommodities } from "./agmarknet-cache";

type FetchOpts = { commodity?: string; state?: string; limit?: number; };

export async function fetchAgmarknet(opts: FetchOpts = {}): Promise<{ records: AgmarknetRecord[]; source: "live" | "cache"; total: number; }> {
  const params = new URLSearchParams({
    "api-key": API_KEY,
    format: "json",
    limit: String(opts.limit || 50),
  });
  if (opts.state) params.set("filters[state]", opts.state);
  if (opts.commodity) params.set("filters[commodity]", opts.commodity);

  try {
    const res = await fetch(`${API_BASE}?${params}`, { next: { revalidate: 900 } }); // 15 min cache
    if (!res.ok) throw new Error(`API ${res.status}`);
    const data = await res.json();
    const records: AgmarknetRecord[] = (data.records || []).map((r: Record<string, string | number>) => ({
      state: r.state as string,
      district: r.district as string,
      market: r.market as string,
      commodity: r.commodity as string,
      variety: r.variety as string,
      grade: r.grade as string,
      arrival_date: r.arrival_date as string,
      min_price: Number(r.min_price),
      max_price: Number(r.max_price),
      modal_price: Number(r.modal_price),
    }));
    return { records, source: "live", total: data.total || records.length };
  } catch (e) {
    // Fallback to cached data
    console.warn("Agmarknet API failed, using cache:", e);
    const cached = opts.commodity === "Onion" ? cachedOnion : [...cachedOnion, ...cachedOtherCommodities];
    return { records: cached, source: "cache", total: cached.length };
  }
}

// Demo helper: show both live and cache side by side
export async function fetchOnionAllMarkets(): Promise<{ live: AgmarknetRecord[]; cache: AgmarknetRecord[]; source: "live" | "cache"; }> {
  const [liveResult, cacheResult] = await Promise.all([
    fetchAgmarknet({ commodity: "Onion", state: "Maharashtra", limit: 30 }),
    Promise.resolve({ records: cachedOnion, source: "cache" as const, total: cachedOnion.length }),
  ]);
  return { live: liveResult.records, cache: cacheResult.records, source: liveResult.source };
}
